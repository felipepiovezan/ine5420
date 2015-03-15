#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  init_buttons_and_sliders();
  init_viewport();
}


void MainWindow::init_buttons_and_sliders(){
//	essa bosta não compila
//	auto zoomSlider = scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0,1,0.1);
//	add(zoomSlider);
}

void MainWindow::init_viewport(){
  CG::Window window(-10, -10, 10, 10);
  _viewport.window(window);

  CG::DisplayFile displayFile; 
  displayFile.add("P1",	CG::GPoint(3, 2));
  displayFile.add("Xaxis", CG::GLine(-1000, 0, 1000, 0));
  displayFile.add("Yaxis", CG::GLine(0, -1000, 0, 1000));
  displayFile.add("Line1", CG::GLine(-20, -4, 5, 3));
  displayFile.add("Line2", CG::GLine(-5, 5, 5, -5));
  _viewport.displayFile(displayFile);
  add(_viewport);
  _viewport.show();
}

//TODO: essa funcao recebe algum sinal da GUI quando o zoom slider mudar
void MainWindow::on_Zoom_Changed(){
	float f = 2; //pegar o float do zoom slider aqui
	_viewport.setWindowZoom(f);
	//redraw everything
}
