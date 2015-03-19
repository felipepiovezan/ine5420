#ifndef OBJECTS_TREE_VIEW_H_
#define OBJECTS_TREE_VIEW_H_

#include <gtkmm.h>
#include "DisplayFile.h"

class ObjectsTreeView : public Gtk::TreeView {
  public:
    ObjectsTreeView(CG::DisplayFile* dfile);
    void refresh();

  protected:
    CG::DisplayFile* displayFile;

    // Objects list widgets
    class ObjectModelColumns : public Gtk::TreeModel::ColumnRecord {
      public:
        ObjectModelColumns() {
          add(colName);
          add(colType);
        }
        Gtk::TreeModelColumn<std::string> colName;
        Gtk::TreeModelColumn<std::string> colType;
    };

    ObjectModelColumns _objectsModelColumns;
    Glib::RefPtr<Gtk::ListStore> _refObjectsTreeModel;

    // Popup menu
    void init_popup_menu();
    Gtk::Menu _menu;

    // Override Signal handler
    virtual bool on_button_press_event(GdkEventButton *ev);

    CG::GObject& getSelectedObject();

    //Signal handlers for popup menu items:
    void on_menu_popup_remove();
    void on_menu_popup_translate();
    void on_menu_popup_scale();
    void on_menu_popup_rotate();
};

#endif
