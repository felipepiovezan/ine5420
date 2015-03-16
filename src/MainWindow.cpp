#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

MainWindow::MainWindow() {
  init_viewport();
  init_handlers();

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

void MainWindow::init_viewport() {
  CG::Window window(-10, -10, 10, 10);
  _viewport.window(window);

  CG::DisplayFile displayFile;
  displayFile.add("P1",	CG::GPoint(3, 2));
  displayFile.add("P2",	CG::GPoint(2, 2));
  displayFile.add("Xaxis", CG::GLine(-1000, 0, 1000, 0));
  displayFile.add("Yaxis", CG::GLine(0, -1000, 0, 1000));
  displayFile.add("Line1", CG::GLine(-20, -4, 5, 3));
  displayFile.add("Line2", CG::GLine(-5, 5, 5, -5));
  _viewport.displayFile(displayFile);
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

// TODO: remove after tests
#include <iostream>

void MainWindow::on_newPoint() {
  std::cout << "new point" << std::endl;
}

void MainWindow::on_newLine() {
  std::cout << "new line" << std::endl;
}

void MainWindow::on_newPolygon() {
  std::cout << "new polygon" << std::endl;
}
