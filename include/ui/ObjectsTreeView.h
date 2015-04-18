#ifndef OBJECTS_TREE_VIEW_H_
#define OBJECTS_TREE_VIEW_H_

#include <gtkmm.h>

#include "cg/World.h"
#include "cg/objects.h"

class ObjectsTreeView : public Gtk::TreeView, public CG::World::WorldListener {
  public:
    ObjectsTreeView(std::shared_ptr<CG::World> world);
    void refresh(const CG::DisplayFile& displayFile);

    // World event handlers
    void onObjectCreation(const std::string& name, CG::ObjRef object);
    void onObjectCreation(const std::string& baseName, const std::vector<CG::ObjRef>& objects);
    void onObjectRemoval(const std::string& name);

  protected:
    std::shared_ptr<CG::World> _world;

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

    const std::string getSelectedObject();

    //Signal handlers for popup menu items:
    void on_menu_popup_remove();
    void on_menu_popup_translate();
    void on_menu_popup_scale();
    void on_menu_popup_rotate();


};

#endif
