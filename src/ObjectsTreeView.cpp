#include "ObjectsTreeView.h"

ObjectsTreeView::ObjectsTreeView() {
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

void ObjectsTreeView::refresh(const CG::DisplayFile& dfile) {
  _refObjectsTreeModel->clear();

  Gtk::TreeModel::Row row;
  for(const auto &it : dfile.objects()){
    row = *(_refObjectsTreeModel->append());
		row[_objectsModelColumns.colName] = it.first;
		row[_objectsModelColumns.colType] = CG::GObject::TypeNames[it.second.type()];
		row[_objectsModelColumns.colObject] = it.second;
	}
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

CG::GObject ObjectsTreeView::getSelectedObject() {
  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = get_selection();
  Gtk::TreeModel::iterator iter = refSelection->get_selected();
  return (*iter)[_objectsModelColumns.colObject];
}

void ObjectsTreeView::on_menu_popup_remove() {
  CG::GObject obj = getSelectedObject();
  // TODO
}

void ObjectsTreeView::on_menu_popup_translate() {
  CG::GObject obj = getSelectedObject();
  // TODO
}

void ObjectsTreeView::on_menu_popup_scale() {
  CG::GObject obj = getSelectedObject();
  // TODO
}

void ObjectsTreeView::on_menu_popup_rotate() {
  CG::GObject obj = getSelectedObject();
  // TODO
}