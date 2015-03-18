#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>
#include "Viewport.h"
#include "DisplayFile.h"
#include "ObjectsTreeView.h"

class Toolbox : public Gtk::Box {
  protected:
    void init_create_widgets();
    void init_control_widgets();
    void init_object_list_widgets();

  public:
    Toolbox();
    void refreshObjectList(const CG::DisplayFile& dfile) { _objectsTreeView.refresh(dfile); }

    // Create widgets
    Gtk::Frame _createFrame;
    Gtk::Box _createBox;
    Gtk::Button _newPoint, _newLine, _newPolygon;

    // Control widgets
    Gtk::Frame _controlFrame;
    Gtk::Box _controlBox, _cBox1, _cBox2;
    Gtk::Button _zoomInBtn, _zoomOutBtn, _leftBtn, _downBtn, _upBtn, _rightBtn;

    // Object list widgets
    Gtk::Frame _objectsFrame;
    Gtk::ScrolledWindow _objectsScroll;
    ObjectsTreeView _objectsTreeView;
};

#endif
