#include "Toolbox.h"

#define TOOLBOX_SPACING 5

Toolbox::Toolbox() :
  Gtk::Box(Gtk::ORIENTATION_VERTICAL, TOOLBOX_SPACING) {
  init_create_widgets();
  init_control_widgets();
  init_object_list_widgets();
}

void Toolbox::init_create_widgets() {
  _createFrame.set_label("Create");
  _newPoint.set_label("Point");
  _newLine.set_label("Line");
  _newPolygon.set_label("Polygon");

  pack_start(_createFrame, Gtk::PACK_SHRINK);
  _createFrame.add(_createBox);

  _createBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  _createBox.set_spacing(TOOLBOX_SPACING);
  _createBox.set_border_width(TOOLBOX_SPACING);

  _createBox.pack_start(_newPoint, Gtk::PACK_EXPAND_WIDGET);
  _createBox.pack_start(_newLine, Gtk::PACK_EXPAND_WIDGET);
  _createBox.pack_start(_newPolygon, Gtk::PACK_EXPAND_WIDGET);

  _createBox.show();
  _newPoint.show();
  _newLine.show();
  _newPolygon.show();
  _createFrame.show();
}

void Toolbox::init_control_widgets() {
  _controlFrame.set_label("Controls");
  _zoomInBtn.set_label("Zoom In");
  _zoomOutBtn.set_label("Zoom Out");
  _leftBtn.set_label("Left");
  _rightBtn.set_label("Right");
  _downBtn.set_label("Down");
  _upBtn.set_label("Up");

  pack_start(_controlFrame, Gtk::PACK_SHRINK);
  _controlFrame.add(_controlBox);
  _controlBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
  _controlBox.set_spacing(TOOLBOX_SPACING);
  _controlBox.set_border_width(TOOLBOX_SPACING);

  _cBox1.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  _cBox2.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  _controlBox.pack_start(_cBox1, Gtk::PACK_SHRINK);
  _controlBox.pack_start(_cBox2, Gtk::PACK_SHRINK);

  _cBox1.pack_start(_zoomInBtn, Gtk::PACK_EXPAND_WIDGET);
  _cBox1.pack_start(_zoomOutBtn, Gtk::PACK_EXPAND_WIDGET);

  _cBox2.pack_start(_leftBtn, Gtk::PACK_EXPAND_WIDGET);
  _cBox2.pack_start(_downBtn, Gtk::PACK_EXPAND_WIDGET);
  _cBox2.pack_start(_upBtn, Gtk::PACK_EXPAND_WIDGET);
  _cBox2.pack_start(_rightBtn, Gtk::PACK_EXPAND_WIDGET);

  _controlFrame.show();
  _controlBox.show();
  _cBox1.show();
  _cBox2.show();
  _zoomInBtn.show();
  _zoomOutBtn.show();
  _leftBtn.show();
  _rightBtn.show();
  _downBtn.show();
  _upBtn.show();
}

void Toolbox::init_object_list_widgets() {
  _refObjectsTreeModel = Gtk::ListStore::create(_objectsModelColumns);
  _objectsTree.set_model(_refObjectsTreeModel);

  _objectsTree.append_column("Name", _objectsModelColumns.colName);
  _objectsTree.append_column("Type", _objectsModelColumns.colType);

  // Filling with test. TODO: show objects from displayFile
  Gtk::TreeModel::Row row = *(_refObjectsTreeModel->append());
  row[_objectsModelColumns.colName] = "Line 1";
  row[_objectsModelColumns.colType] = "Line";
  row = *(_refObjectsTreeModel->append());
  row[_objectsModelColumns.colName] = "P3";
  row[_objectsModelColumns.colType] = "Point";

  //Make all the columns reorderable
  for(guint i = 0; i < 2; i++) {
    Gtk::TreeView::Column* pColumn = _objectsTree.get_column(i);
    pColumn->set_reorderable();
  }

  // Layouting
  pack_start(_objectsFrame, Gtk::PACK_EXPAND_WIDGET);
  _objectsFrame.set_label("Object List");
  _objectsFrame.add(_objectsTree);
  _objectsTree.show();
  _objectsFrame.show();
}

void Toolbox::refreshObjectList(const CG::DisplayFile& dfile) {
  _refObjectsTreeModel->clear();

  Gtk::TreeModel::Row row;
  for(const auto &it : dfile.objects()){
    row = *(_refObjectsTreeModel->append());
		row[_objectsModelColumns.colName] = it.first;
		row[_objectsModelColumns.colType] = CG::GObject::TypeNames[it.second.type()];
	}
}
