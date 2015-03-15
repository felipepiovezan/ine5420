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

  // Event handlers
  _newPoint.signal_clicked().connect(sigc::mem_fun(*this, &Toolbox::on_newPoint_clicked));
  _newLine.signal_clicked().connect(sigc::mem_fun(*this, &Toolbox::on_newLine_clicked));
  _newPolygon.signal_clicked().connect(sigc::mem_fun(*this, &Toolbox::on_newPolygon_clicked));

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

  pack_start(_controlFrame, Gtk::PACK_SHRINK);
  _controlFrame.add(_controlBox);
  _controlBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  _controlBox.set_spacing(TOOLBOX_SPACING);
  _controlBox.set_border_width(TOOLBOX_SPACING);

  _controlBox.pack_start(_zoomInBtn, Gtk::PACK_EXPAND_WIDGET);
  _controlBox.pack_start(_zoomOutBtn, Gtk::PACK_EXPAND_WIDGET);

  _zoomInBtn.signal_clicked().connect(sigc::mem_fun(*this, &Toolbox::on_zoomIn_clicked));
  _zoomOutBtn.signal_clicked().connect(sigc::mem_fun(*this, &Toolbox::on_zoomOut_clicked));

  _controlFrame.show();
  _controlBox.show();
  _zoomInBtn.show();
  _zoomOutBtn.show();
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

// TODO: remove after tests
#include <iostream>

void Toolbox::on_newPoint_clicked() {
  std::cout << "new point" << std::endl;
}

void Toolbox::on_newLine_clicked() {
  std::cout << "new line" << std::endl;
}

void Toolbox::on_newPolygon_clicked() {
  std::cout << "new polygon" << std::endl;
}

void Toolbox::on_zoomIn_clicked() {
  std::cout << "zoom in" << std::endl;
}

void Toolbox::on_zoomOut_clicked() {
  std::cout << "zoom out" << std::endl;
}
