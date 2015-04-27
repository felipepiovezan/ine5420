#include "ui/ObjectsTreeView.h"

#include "ui/dialogs.h"

ObjectsTreeView::ObjectsTreeView(std::shared_ptr<CG::World> world) :
_world(world) {
  _refObjectsTreeModel = Gtk::ListStore::create(_objectsModelColumns);
  set_model(_refObjectsTreeModel);

  append_column("Name", _objectsModelColumns.colName);
  append_column("Type", _objectsModelColumns.colType);

  // _refObjectsTreeModel->set_sort_column(0, Gtk::SORT_ASCENDING);

  //Make all the columns reorderable
  for(guint i = 0; i < 2; i++) {
    Gtk::TreeView::Column* pColumn = get_column(i);
    pColumn->set_reorderable();
  }

  init_popup_menu();
}

void ObjectsTreeView::init_popup_menu() {
  Gtk::MenuItem* item;

  item = Gtk::manage(new Gtk::MenuItem("Remove", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_remove) );
  _menu.append(*item);

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

void ObjectsTreeView::on_menu_popup_remove() {
  const std::string name = getSelectedObject();
  _world->removeObject(name);
}

void ObjectsTreeView::on_menu_popup_translate() {
  const std::string name = getSelectedObject();

  TranslateDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    CG::Coordinate c = dialog.getCoordinate();
		_world->translateObject(name, c.x, c.y, c.z);
  }
}

void ObjectsTreeView::on_menu_popup_scale() {
  const std::string name = getSelectedObject();
  ScaleDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    CG::Coordinate scale = dialog.getCoordinate();
		_world->scaleObject(name, scale.x, scale.y, scale.z);
  }
}

void ObjectsTreeView::on_menu_popup_rotate() {
	const std::string name = getSelectedObject();

	RotateDialog dialog;

	if (dialog.run() == Gtk::RESPONSE_OK) {
    double xRotation = dialog.getXRotation();
    double yRotation = dialog.getYRotation();
		double zRotation = dialog.getZRotation();

		if (dialog.isAroundObjectCenterSelected()) {
			_world->rotateObject(name, xRotation, yRotation, zRotation);
		} else {
			CG::Coordinate rotationCenter = dialog.getRotationCenter();
			_world->rotateObject(name, xRotation, yRotation, zRotation, rotationCenter);
		}
  }
}

void ObjectsTreeView::onObjectCreation(const std::string& name, CG::ObjRef object) {
  Gtk::TreeModel::Row row = *(_refObjectsTreeModel->append());
  row[_objectsModelColumns.colName] = name;
  row[_objectsModelColumns.colType] = object->typeName();
}

void ObjectsTreeView::onObjectCreation(const std::string& baseName, const std::vector<CG::ObjRef>& objects) {
  int i = 0;
  for(const auto &obj : objects) {
    auto name = baseName + std::to_string(i++);
    onObjectCreation(name, obj);
  }
}

void ObjectsTreeView::onObjectRemoval(const std::string& name) {
  for (auto row : _refObjectsTreeModel->children()) {
    std::string rowName = (*row)[_objectsModelColumns.colName];
    if (rowName == name) {
      _refObjectsTreeModel->erase(row);
    }
  }
}
