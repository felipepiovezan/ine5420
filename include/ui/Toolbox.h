#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>

#include "cg/World.h"
#include "ui/ObjectsTreeView.h"
#include "ui/widgets.h"

class Toolbox : public Gtk::VBox {
  protected:
    void init_create_widgets();
    void init_control_widgets();
    void init_object_list_widgets();
    void set_icon(Gtk::Button& btn, Gtk::Image& img, const Gtk::StockID& id);

  public:
    Toolbox(std::shared_ptr<CG::World> world);

    // Create widgets
    Gtk::Frame _createFrame;
    Grid _createGrid;
    Gtk::Button _newPoint, _newLine, _newPolygon, _newCurve, _newSurface;

    // Control widgets
    Gtk::Frame _controlFrame;
    Grid _controlsGrid;
    Gtk::Button _zoomInBtn, _zoomOutBtn, _leftBtn, _downBtn, _upBtn, _rightBtn,
                _rotateLeftBtn, _rotateRightBtn;
    Gtk::Image _zoomInImg, _zoomOutImg, _leftImg, _rightImg, _upImg, _downImg,
                _rotateLeftImg, _rotateRightImg;
    // Bend controls
    Gtk::Button _bendLeftBtn, _bendRightBtn, _bendForwardBtn, _bendBackwardBtn;
    Gtk::Image _bendLeftImg, _bendRightImg, _bendForwardImg, _bendBackwardImg;

    // Object list widgets
    Gtk::Frame _objectsFrame;
    Gtk::ScrolledWindow _objectsScroll;
    ObjectsTreeView _objectsTreeView;
};

#endif
