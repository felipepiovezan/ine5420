#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <gtkmm.h>

class Toolbox : public Gtk::Box {
  public:
    Toolbox();

  protected:
    void init_create_widgets();
    void init_zoom_widgets();
    void init_object_list_widgets();

    // Create widgets
    Gtk::Frame _createFrame;
    Gtk::Box _createBox;
    Gtk::Button _newPoint, _newLine, _newPolygon;
    void on_newPoint_clicked();
    void on_newLine_clicked();
    void on_newPolygon_clicked();

    // Zoom widgets
    Gtk::Frame _zoomFrame;
    Gtk::Scale _zoomScale;

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
