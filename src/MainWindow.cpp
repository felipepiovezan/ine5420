#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

#include <iostream>

MainWindow::MainWindow() :
  _window(-10, -10, 10, 10),
  _displayFile(),
  _viewport(&_window, &_displayFile) {

  init_examples();
  init_handlers();

  _toolbox.refreshObjectList(_displayFile);
  _viewport.redraw();

  // Layouting
  set_title("Computer Graphics Interative System");
  set_border_width(10);

  add(_mainBox);
  _mainBox.set_spacing(10);
  _mainBox.show();

  _mainBox.pack_start(_toolbox, Gtk::PACK_SHRINK);
  _toolbox.set_size_request(200, 0);
  _mainBox.pack_end(_viewport, Gtk::PACK_EXPAND_WIDGET);
  _viewport.set_size_request(550, 550);

  _toolbox.show();
  _viewport.show();
}

void MainWindow::init_examples() {
  _displayFile.add("Xaxis", CG::GLine(-1000, 0, 1000, 0));
  _displayFile.add("Yaxis", CG::GLine(0, -1000, 0, 1000));
  _displayFile.add("Example Point",	CG::GPoint(-3, 2));
  _displayFile.add("Example Line", CG::GLine(-10, -4, 5, 3));
  CG::GObject::Coordinates coords;
  coords.push_back(CG::Coordinate(5, -4));
  coords.push_back(CG::Coordinate(3, -1));
  coords.push_back(CG::Coordinate(2, 4));
  coords.push_back(CG::Coordinate(7, 5));
  coords.push_back(CG::Coordinate(6, 2));
  _displayFile.add("Example Polygon",	CG::GPolygon(coords));

  init_leaf();
}

void MainWindow::init_handlers() {
  _toolbox._newPoint.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPoint));
  _toolbox._newLine.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newLine));
  _toolbox._newPolygon.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPolygon));

  _toolbox._zoomInBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_zoomIn));
  _toolbox._zoomOutBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_zoomOut));
  _toolbox._leftBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_left));
  _toolbox._rightBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_right));
  _toolbox._upBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_up));
  _toolbox._downBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_down));
}

void MainWindow::on_newPoint() {
  NamedPointDialog pointDialog;
  if (pointDialog.run() == Gtk::RESPONSE_OK) {
    createPoint(pointDialog.getName(), pointDialog.getCoordinate());
  }
}

void MainWindow::on_newLine() {
  LineDialog lineDialog;
  if (lineDialog.run() == Gtk::RESPONSE_OK) {
    createLine(lineDialog.getName(), lineDialog.getCoordinate1(), lineDialog.getCoordinate2());
  }
}

void MainWindow::on_newPolygon() {
  PolygonDialog polygonDialog;
  if (polygonDialog.run() == Gtk::RESPONSE_OK) {
    createPolygon(polygonDialog.getName(), polygonDialog.getCoordinates());
  }
}

void MainWindow::createPoint(std::string name, CG::Coordinate c) {
  CG::GPoint point(c);
  _viewport.addObject(name, point);
  _toolbox.refreshObjectList(_displayFile);
}

void MainWindow::createLine(std::string name, CG::Coordinate c1, CG::Coordinate c2) {
  CG::GLine line(c1, c2);
  _viewport.addObject(name, line);
  _toolbox.refreshObjectList(_displayFile);
}

void MainWindow::createPolygon(std::string name, CG::GObject::Coordinates coordinates) {
  CG::GPolygon polygon(coordinates);
  _viewport.addObject(name, polygon);
  _toolbox.refreshObjectList(_displayFile);
}

void MainWindow::init_leaf(){
  _displayFile.add("Leaf_00", CG::GLine(-2,3,-1,4));
  _displayFile.add("Leaf_01", CG::GLine(-1,4,0,6) );
  _displayFile.add("Leaf_02", CG::GLine(-6,-1,-2,-4));
  _displayFile.add("Leaf_03", CG::GLine(-2,-4,0,-5) );
  _displayFile.add("Leaf_04", CG::GLine(0,-5,2,-3));
  _displayFile.add("Leaf_05", CG::GLine(2,-3,3,0));
  _displayFile.add("Leaf_06", CG::GLine(3,0,4,5));
  _displayFile.add("Leaf_07", CG::GLine(-5,3,-4,2));
  _displayFile.add("Leaf_08", CG::GLine(-4,2,-1,1) );
  _displayFile.add("Leaf_09", CG::GLine(5,-3,3,-4));
  _displayFile.add("Leaf_10", CG::GLine(3,-4,1,-4) );
  _displayFile.add("Leaf_11", CG::GLine(1,-4,1,-1));
  _displayFile.add("Leaf_12", CG::GLine(1,-1,2,1) );
  _displayFile.add("Leaf_13", CG::GLine(-1,-10,0,-6));
  _displayFile.add("Leaf_14", CG::GLine(0,-6,-2,-7));
  _displayFile.add("Leaf_15", CG::GLine(-2,-7,-3,-7));
  _displayFile.add("Leaf_16", CG::GLine(-3,-7,-6,-6));
  _displayFile.add("Leaf_17", CG::GLine(-6,-6,-5,-5));
  _displayFile.add("Leaf_18", CG::GLine(-5,-5,-8,-3));
  _displayFile.add("Leaf_19", CG::GLine(-8,-3,-7,-3));
  _displayFile.add("Leaf_20", CG::GLine(-7,-3,-8,-1));
  _displayFile.add("Leaf_21", CG::GLine(-8,-1,-8,1));
  _displayFile.add("Leaf_22", CG::GLine(-8,1,-6,0));
  _displayFile.add("Leaf_23", CG::GLine(-6,0,-5,0));
  _displayFile.add("Leaf_24", CG::GLine(-5,0,-3,-1));
  _displayFile.add("Leaf_25", CG::GLine(-3,-1,-7,3));
  _displayFile.add("Leaf_26", CG::GLine(-7,3,-5,4));
  _displayFile.add("Leaf_27", CG::GLine(-5,4,-6,6));
  _displayFile.add("Leaf_28", CG::GLine(-6,6,-5,6));
  _displayFile.add("Leaf_29", CG::GLine(-5,6,-5,10));
  _displayFile.add("Leaf_30", CG::GLine(-5,10,-4,8));
  _displayFile.add("Leaf_31", CG::GLine(-4,8,-2,8));
  _displayFile.add("Leaf_32", CG::GLine(-2,8,-1,6));
  _displayFile.add("Leaf_33", CG::GLine(-1,6,0,8));
  _displayFile.add("Leaf_34", CG::GLine(0,8,1,6));
  _displayFile.add("Leaf_35", CG::GLine(1,6,1,2));
  _displayFile.add("Leaf_36", CG::GLine(1,2,2,5));
  _displayFile.add("Leaf_37", CG::GLine(2,5,3,5));
  _displayFile.add("Leaf_38", CG::GLine(3,5,4,7));
  _displayFile.add("Leaf_39", CG::GLine(4,7,5,5));
  _displayFile.add("Leaf_40", CG::GLine(5,5,6,5));
  _displayFile.add("Leaf_41", CG::GLine(6,5,5,2));
  _displayFile.add("Leaf_42", CG::GLine(5,2,6,2));
  _displayFile.add("Leaf_43", CG::GLine(6,2,6,1));
  _displayFile.add("Leaf_44", CG::GLine(6,1,4,-2));
  _displayFile.add("Leaf_45", CG::GLine(4,-2,7,-2));
  _displayFile.add("Leaf_46", CG::GLine(7,-2,6,-4));
  _displayFile.add("Leaf_47", CG::GLine(6,-4,4,-5));
  _displayFile.add("Leaf_48", CG::GLine(4,-5,5,-6));
  _displayFile.add("Leaf_49", CG::GLine(5,-6,4,-7));
  _displayFile.add("Leaf_50", CG::GLine(4,-7,3,-7));
  _displayFile.add("Leaf_51", CG::GLine(3,-7,1,-6));
  _displayFile.add("Leaf_52", CG::GLine(1,-6,0,-6));
  _displayFile.add("Leaf_53", CG::GLine(0,-6,0,-3));
  _displayFile.add("Leaf_54", CG::GLine(0,-3,-1,1));
  _displayFile.add("Leaf_55", CG::GLine(-1,1,-4,7));
  _displayFile.add("Leaf_56", CG::GLine(-2,-4,-3,-5));
  _displayFile.add("Leaf_57", CG::GLine(-3,-5,-5,-6));
  _displayFile.add("Leaf_58", CG::GLine(-2,7,-3,5));
  _displayFile.add("Leaf_59", CG::GLine(1,-1,0,0));
}
