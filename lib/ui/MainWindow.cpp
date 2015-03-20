#include "ui/MainWindow.h"

#include <iostream>
#include "cg/Window.h"
#include "cg/DisplayFile.h"

MainWindow::MainWindow() :
  _window(-10, -10, 10, 10),
  _displayFile(),
  _viewport(&_window, &_displayFile),
  _toolbox(&_displayFile) {

  init_examples();
  init_handlers();

  _toolbox.refreshObjectList();
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
  CG::GLine x(-1000, 0, 1000, 0);
  x.color = CG::Color(1, 0, 0);
  _displayFile.add("Xaxis", x);

  CG::GLine y(0, -1000, 0, 1000);
  y.color = CG::Color(0, 0, 1);
  _displayFile.add("Yaxis", y);

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
    createPoint(pointDialog.getName(), pointDialog.getColor(), pointDialog.getCoordinate());
  }
}

void MainWindow::on_newLine() {
  LineDialog lineDialog;
  if (lineDialog.run() == Gtk::RESPONSE_OK) {
    createLine(lineDialog.getName(), lineDialog.getColor(), lineDialog.getCoordinate1(), lineDialog.getCoordinate2());
  }
}

void MainWindow::on_newPolygon() {
  PolygonDialog polygonDialog;
  if (polygonDialog.run() == Gtk::RESPONSE_OK) {
    createPolygon(polygonDialog.getName(), polygonDialog.getColor(), polygonDialog.getCoordinates());
  }
}

void MainWindow::createPoint(std::string name, CG::Color color, CG::Coordinate c) {
  CG::GPoint point(c);
  point.color = color;
  _displayFile.add(name, point);
  _toolbox.refreshObjectList();
}

void MainWindow::createLine(std::string name, CG::Color color, CG::Coordinate c1, CG::Coordinate c2) {
  CG::GLine line(c1, c2);
  line.color = color;
  _displayFile.add(name, line);
  _toolbox.refreshObjectList();
}

void MainWindow::createPolygon(std::string name, CG::Color color, CG::GObject::Coordinates coordinates) {
  CG::GPolygon polygon(coordinates);
  polygon.color = color;
  _displayFile.add(name, polygon);
  _toolbox.refreshObjectList();
}

void MainWindow::init_leaf(){
/*  _displayFile.add("Leaf_00", CG::GLine(-2,3,-1,4));
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
  _displayFile.add("Leaf_53", CG::GLine(0,-6,0,-3));
  _displayFile.add("Leaf_54", CG::GLine(0,-3,-1,1));
  _displayFile.add("Leaf_55", CG::GLine(-1,1,-4,7));
  _displayFile.add("Leaf_56", CG::GLine(-2,-4,-3,-5));
  _displayFile.add("Leaf_57", CG::GLine(-3,-5,-5,-6));
  _displayFile.add("Leaf_58", CG::GLine(-2,7,-3,5));
  _displayFile.add("Leaf_59", CG::GLine(1,-1,0,0));*/
  CG::GObject::Coordinates c;
  c.push_back(CG::Coordinate(-1,-10));
  c.push_back(CG::Coordinate(0,-6));
  c.push_back(CG::Coordinate(-2,-7));
  c.push_back(CG::Coordinate(-3,-7));
  c.push_back(CG::Coordinate(-6,-6));
  c.push_back(CG::Coordinate(-5,-5));
  c.push_back(CG::Coordinate(-8,-3));
  c.push_back(CG::Coordinate(-7,-3));
  c.push_back(CG::Coordinate(-8,-1));
  c.push_back(CG::Coordinate(-8,1));
  c.push_back(CG::Coordinate(-6,0));
  c.push_back(CG::Coordinate(-5,0));
  c.push_back(CG::Coordinate(-3,-1));
  c.push_back(CG::Coordinate(-7,3));
  c.push_back(CG::Coordinate(-5,4));
  c.push_back(CG::Coordinate(-6,6));
  c.push_back(CG::Coordinate(-5,6));
  c.push_back(CG::Coordinate(-5,10));
  c.push_back(CG::Coordinate(-4,8));
  c.push_back(CG::Coordinate(-2,8));
  c.push_back(CG::Coordinate(-1,6));
  c.push_back(CG::Coordinate(0,8));
  c.push_back(CG::Coordinate(1,6));
  c.push_back(CG::Coordinate(1,2));
  c.push_back(CG::Coordinate(2,5));
  c.push_back(CG::Coordinate(3,5));
  c.push_back(CG::Coordinate(4,7));
  c.push_back(CG::Coordinate(5,5));
  c.push_back(CG::Coordinate(6,5));
  c.push_back(CG::Coordinate(5,2));
  c.push_back(CG::Coordinate(6,2));
  c.push_back(CG::Coordinate(6,1));
  c.push_back(CG::Coordinate(4,-2));
  c.push_back(CG::Coordinate(7,-2));
  c.push_back(CG::Coordinate(6,-4));
  c.push_back(CG::Coordinate(4,-5));
  c.push_back(CG::Coordinate(5,-6));
  c.push_back(CG::Coordinate(4,-7));
  c.push_back(CG::Coordinate(3,-7));
  c.push_back(CG::Coordinate(1,-6));
  c.push_back(CG::Coordinate(0,-6));
  c.push_back(CG::Coordinate(-1,-10));
  auto leaf = CG::GPolygon(c);
  leaf.color = CG::Color(0, 1, 0);
  _displayFile.add("leaf body", leaf);
}
