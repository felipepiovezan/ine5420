#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>
#include "Viewport.h"
#include "DisplayFile.h"

class Toolbox : public Gtk::Box {
  protected:
    void init_create_widgets();
    void init_control_widgets();
    void init_object_list_widgets();

  public:
    Toolbox();
    void refreshObjectList(const CG::DisplayFile& dfile);

    // Create widgets
    Gtk::Frame _createFrame;
    Gtk::Box _createBox;
    Gtk::Button _newPoint, _newLine, _newPolygon;

    // Control widgets
    Gtk::Frame _controlFrame;
    Gtk::Box _controlBox, _cBox1, _cBox2;
    Gtk::Button _zoomInBtn, _zoomOutBtn, _leftBtn, _downBtn, _upBtn, _rightBtn;

    // Objects list widgets
    class ObjectModelColumns : public Gtk::TreeModel::ColumnRecord {
      public:
        ObjectModelColumns() {
          add(colName);
          add(colType);
        }
        Gtk::TreeModelColumn<Glib::ustring> colName;
        Gtk::TreeModelColumn<Glib::ustring> colType;
    };
    Gtk::Frame _objectsFrame;
    Gtk::ScrolledWindow _objectsScroll;
    Gtk::TreeView _objectsTree;
    ObjectModelColumns _objectsModelColumns;
    Glib::RefPtr<Gtk::ListStore> _refObjectsTreeModel;
};

#endif
