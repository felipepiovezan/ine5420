#include "ui/ObjectsTreeView.h"

#include "ui/dialogs.h"

ObjectsTreeView::ObjectsTreeView(CG::World& world) :
world(&world) {
  _refObjectsTreeModel = Gtk::ListStore::create(_objectsModelColumns);
  set_model(_refObjectsTreeModel);

  append_column("Name", _objectsModelColumns.colName);
  append_column("Type", _objectsModelColumns.colType);

  //Make all the columns reorderable
  for(guint i = 0; i < 2; i++) {
    Gtk::TreeView::Column* pColumn = get_column(i);
    pColumn->set_reorderable();
  }

  init_popup_menu();
}

void ObjectsTreeView::init_popup_menu() {
  Gtk::MenuItem* item;

  item = Gtk::manage(new Gtk::MenuItem("Translate...", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_translate) );
  _menu.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Scale...", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_scale) );
  _menu.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Rotate...", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_rotate) );
  _menu.append(*item);

  _menu.accelerate(*this);
  _menu.show_all(); //Show all menu items when the menu pops up

  signal_button_press_event().connect(sigc::mem_fun(*this, &ObjectsTreeView::on_button_press_event), false);
}

bool ObjectsTreeView::on_button_press_event(GdkEventButton* event) {
  bool return_value = false;

  // Call base class, to allow normal handling,
  // such as allowing the row to be selected by the right-click:
  return_value = TreeView::on_button_press_event(event);

  // Then call the popup menu
  if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
    _menu.popup(event->button, event->time);
  }

  return return_value;
}

const std::string ObjectsTreeView::getSelectedObject() {
  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = get_selection();
  Gtk::TreeModel::iterator iter = refSelection->get_selected();
  return (*iter)[_objectsModelColumns.colName];
}

void ObjectsTreeView::on_menu_popup_translate() {
  const std::string name = getSelectedObject();

  TranslateDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    CG::Coordinate c = dialog.getCoordinate();
		world->translateObject(name, c.x, c.y);
  }
}

void ObjectsTreeView::on_menu_popup_scale() {
  const std::string name = getSelectedObject();
  ScaleDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    CG::Coordinate scale = dialog.getCoordinate();
		world->scaleObject(name, scale.x, scale.y);
  }
}

void ObjectsTreeView::on_menu_popup_rotate() {
	const std::string name = getSelectedObject();

	RotateDialog dialog;

	if (dialog.run() == Gtk::RESPONSE_OK) {
		double degrees = dialog.getRotation();

		if (dialog.isAroundObjectCenterSelected()) {
			world->rotateObject(name, degrees);
		} else {
			CG::Coordinate rotationCenter = dialog.getRotationCenter();
			world->rotateObject(name, degrees, rotationCenter);
		}
  }
}

void ObjectsTreeView::onObjectCreation(const std::string& name, const CG::GObject& object) {
  Gtk::TreeModel::Row row = *(_refObjectsTreeModel->append());
  row[_objectsModelColumns.colName] = name;
  row[_objectsModelColumns.colType] = CG::GObject::TypeNames[object.type()];
}
