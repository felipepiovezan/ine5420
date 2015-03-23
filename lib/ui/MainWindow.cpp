#include "ui/MainWindow.h"

#include <iostream>
#include "cg/Window.h"
#include "cg/DisplayFile.h"

MainWindow::MainWindow() :
	_window(0, 0, 10, 10, 0),
	_displayFile(),
	_viewport(&_window, &_displayFile),
	_toolbox(&_viewport) {
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
  _displayFile.add("Xaxis", x, _window.wo2wiMatrix());

  CG::GLine y(0, -1000, 0, 1000);
  y.color = CG::Color(0, 0, 1);
  _displayFile.add("Yaxis", y, _window.wo2wiMatrix());

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

  _toolbox._rotateLeftBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_rotate_left));
  _toolbox._rotateRightBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_rotate_right));
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
  _displayFile.add(name, point, _window.wo2wiMatrix());
  _toolbox.refreshObjectList();
}

void MainWindow::createLine(std::string name, CG::Color color, CG::Coordinate c1, CG::Coordinate c2) {
  CG::GLine line(c1, c2);
  line.color = color;
  _displayFile.add(name, line, _window.wo2wiMatrix());
  _toolbox.refreshObjectList();
}

//TODO: change the coordinates parameter to &&, since that's the only way it's being called;
void MainWindow::createPolygon(std::string name, CG::Color color, CG::GObject::Coordinates coordinates) {
  CG::GPolygon polygon(coordinates);
  polygon.color = color;
  _displayFile.add(name, polygon, _window.wo2wiMatrix());
  _toolbox.refreshObjectList();
}

void MainWindow::init_leaf(){
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
  _displayFile.add("leaf body", leaf, _window.wo2wiMatrix());
}