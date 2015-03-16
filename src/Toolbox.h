#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>
#include "Viewport.h"

class Toolbox : public Gtk::Box {
  protected:
    void init_create_widgets();
    void init_control_widgets();
    void init_object_list_widgets();

  public:
    Toolbox();

    // Create widgets
    Gtk::Frame _createFrame;
    Gtk::Box _createBox;
    Gtk::Button _newPoint, _newLine, _newPolygon;

    // Control widgets
    Gtk::Frame _controlFrame;
    Gtk::Box _controlBox;
    Gtk::Button _zoomInBtn, _zoomOutBtn;

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
    Gtk::TreeView _objectsTree;
    ObjectModelColumns _objectsModelColumns;
    Glib::RefPtr<Gtk::ListStore> _refObjectsTreeModel;
};

#endif
