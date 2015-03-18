#ifndef OBJECTS_TREE_VIEW_H_
#define OBJECTS_TREE_VIEW_H_

#include <gtkmm.h>
#include "DisplayFile.h"

class ObjectsTreeView : public Gtk::TreeView {
  public:
    ObjectsTreeView();
    void refresh(const CG::DisplayFile& dfile);

  protected:
    // Objects list widgets
    class ObjectModelColumns : public Gtk::TreeModel::ColumnRecord {
      public:
        ObjectModelColumns() {
          add(colName);
          add(colType);
          add(colObject);
        }
        Gtk::TreeModelColumn<Glib::ustring> colName;
        Gtk::TreeModelColumn<Glib::ustring> colType;
        Gtk::TreeModelColumn<CG::GObject> colObject;
    };

    ObjectModelColumns _objectsModelColumns;
    Glib::RefPtr<Gtk::ListStore> _refObjectsTreeModel;


    // Popup menu
    void init_popup_menu();
    Gtk::Menu _menu;

    // Override Signal handler
    virtual bool on_button_press_event(GdkEventButton *ev);

    //Signal handlers for popup menu items:
    CG::GObject getSelectedObject();
    void on_menu_popup_remove();
    void on_menu_popup_translate();
    void on_menu_popup_scale();
    void on_menu_popup_rotate();
};

#endif