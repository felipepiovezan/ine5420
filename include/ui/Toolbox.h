#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>
#include "cg/DisplayFile.h"
#include "cg/Viewport.h"
#include "ui/ObjectsTreeView.h"

class Toolbox : public Gtk::Box {
  protected:
    void init_create_widgets();
    void init_control_widgets();
    void init_object_list_widgets();
    void set_icon(Gtk::Button& btn, Gtk::Image& img, const Gtk::StockID& id);

  public:
    Toolbox(CG::Viewport* viewport);
    void refreshObjectList() { _objectsTreeView.refresh(); }

    // Create widgets
    Gtk::Frame _createFrame;
    Gtk::Box _createBox;
    Gtk::Button _newPoint, _newLine, _newPolygon;

    // Control widgets
    Gtk::Frame _controlFrame;
    Gtk::Box _controlBox, _cBox1, _cBox2, _cBox3;
    Gtk::Button _zoomInBtn, _zoomOutBtn, _leftBtn, _downBtn, _upBtn, _rightBtn,
                _rotateLeftBtn, _rotateRightBtn;
    Gtk::Image _zoomInImg, _zoomOutImg, _leftImg, _rightImg, _upImg, _downImg,
                _rotateLeftImg, _rotateRightImg;

    // Object list widgets
    Gtk::Frame _objectsFrame;
    Gtk::ScrolledWindow _objectsScroll;
    ObjectsTreeView _objectsTreeView;
};

#endif
