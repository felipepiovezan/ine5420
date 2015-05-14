#include "ui/Toolbox.h"

#define TOOLBOX_SPACING 5

Toolbox::Toolbox(std::shared_ptr<CG::World> world) : _objectsTreeView(world) {
  set_spacing(TOOLBOX_SPACING);
  init_create_widgets();
  init_control_widgets();
  init_object_list_widgets();
}

void Toolbox::init_create_widgets() {
  _createFrame.set_label("Create");
  _newPoint.set_label("Point");
  _newLine.set_label("Line");
  _newPolygon.set_label("Polygon");
  _newCurve.set_label("Curve");
  _newSurface.set_label("Surface");

  pack_start(_createFrame, Gtk::PACK_SHRINK);
  _createFrame.add(_createGrid);

  _createGrid.attach(_newPoint, 0, 0, 1, 1);
  _createGrid.attach(_newLine, 1, 0, 1, 1);
  _createGrid.attach(_newPolygon, 0, 1, 1, 1);
  _createGrid.attach(_newCurve, 1, 1, 1, 1);
  _createGrid.attach(_newSurface, 0, 2, 2, 1);

  _newPoint.show();
  _newLine.show();
  _newPolygon.show();
  _newCurve.show();
  _newSurface.show();
  _createGrid.show();
  _createFrame.show();
}

void Toolbox::init_control_widgets() {
  _controlFrame.set_label("Controls");
  set_icon(_leftBtn, _leftImg, Gtk::Stock::GO_BACK);
  set_icon(_rightBtn, _rightImg, Gtk::Stock::GO_FORWARD);
  set_icon(_upBtn, _upImg, Gtk::Stock::GO_UP);
  set_icon(_downBtn, _downImg, Gtk::Stock::GO_DOWN);
  set_icon(_zoomInBtn, _zoomInImg, Gtk::Stock::ZOOM_IN);
  set_icon(_zoomOutBtn, _zoomOutImg, Gtk::Stock::ZOOM_OUT);
  set_icon(_rotateLeftBtn, _rotateLeftImg, Gtk::Stock::UNDO);
  set_icon(_rotateRightBtn, _rotateRightImg, Gtk::Stock::REDO);
  set_icon(_bendLeftBtn, _bendLeftImg, Gtk::Stock::GOTO_FIRST);
  set_icon(_bendRightBtn, _bendRightImg, Gtk::Stock::GOTO_LAST);
  set_icon(_bendForwardBtn, _bendForwardImg, Gtk::Stock::GOTO_TOP);
  set_icon(_bendBackwardBtn, _bendBackwardImg, Gtk::Stock::GOTO_BOTTOM);

  pack_start(_controlFrame, Gtk::PACK_SHRINK);
  _controlFrame.add(_controlsGrid);

  int line = 0;
  _controlsGrid.attach(_zoomInBtn, 0, line, 2, 1);
  _controlsGrid.attach(_upBtn, 2, line, 2, 1);
  _controlsGrid.attach(_zoomOutBtn, 4, line, 2, 1);

  line++;
  _controlsGrid.attach(_leftBtn, 0, line, 3, 1);
  _controlsGrid.attach(_rightBtn, 3, line, 3, 1);

  line++;
  _controlsGrid.attach(_rotateLeftBtn, 0, line, 2, 1);
  _controlsGrid.attach(_downBtn, 2, line, 2, 1);
  _controlsGrid.attach(_rotateRightBtn, 4, line, 2, 1);

  line++;
  _controlsGrid.attach(_bendForwardBtn, 0, line, 6, 1);

  line++;
  _controlsGrid.attach(_bendLeftBtn, 0, line, 3, 1);
  _controlsGrid.attach(_bendRightBtn, 3, line, 3, 1);

  line++;
  _controlsGrid.attach(_bendBackwardBtn, 0, line, 6, 1);

  _zoomInBtn.show();
  _zoomOutBtn.show();
  _leftBtn.show();
  _rightBtn.show();
  _downBtn.show();
  _upBtn.show();
  _rotateLeftBtn.show();
  _rotateRightBtn.show();
  _bendLeftBtn.show();
  _bendRightBtn.show();
  _bendForwardBtn.show();
  _bendBackwardBtn.show();
  _controlsGrid.show();
  _controlFrame.show();
}

void Toolbox::init_object_list_widgets() {
  pack_start(_objectsFrame, Gtk::PACK_EXPAND_WIDGET);
  _objectsFrame.set_label("Object List");
  _objectsScroll.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
  _objectsScroll.set_border_width(TOOLBOX_SPACING);

  _objectsFrame.add(_objectsScroll);
  _objectsScroll.add(_objectsTreeView);

  _objectsTreeView.show();
  _objectsScroll.show();
  _objectsFrame.show();
}

void Toolbox::set_icon(Gtk::Button& btn, Gtk::Image& img, const Gtk::StockID& id) {
  Gtk::Stock::lookup(id, Gtk::ICON_SIZE_BUTTON, img);
  btn.add(img);
  img.show();
}
