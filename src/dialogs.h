#ifndef DIALOGS_H_
#define DIALOGS_H_

#include <gtkmm.h>
#include <string>
#include "GObject.h"
#include "MainWindow.h"

/**
 * Custom widget to request an object name
 */
class ObjectNameBox : public Gtk::Box {
  public:
    ObjectNameBox();
    Gtk::Label label;
    Gtk::Entry name;

    std::string getName();
};

/**
 * Custom widget to request a single coordinate
 */
class CoordinateBox : public Gtk::Box {
  public:
    CoordinateBox();
    Gtk::Label labelX, labelY;
    Gtk::Entry entryX, entryY;

    CG::Coordinate getCoordinate();
};

/**
 * Dialog window to request a coordinate
 */
class PointDialog : public Gtk::Dialog {
  public:
    PointDialog();
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    CoordinateBox coordBox;
};

/**
 * Dialog window to request a coordinate and the point name
 */
class NamedPointDialog : public PointDialog {
  public:
    NamedPointDialog();
    std::string getName() { return nameBox.getName(); }

  protected:
    ObjectNameBox nameBox;
};

/**
 * Dialog window to request data for a Line
 */
class LineDialog : public Gtk::Dialog {
  public:
    LineDialog();

    std::string getName() { return nameBox.getName(); }
    CG::Coordinate getCoordinate1() { return coordBox1.getCoordinate(); }
    CG::Coordinate getCoordinate2() { return coordBox2.getCoordinate(); }

  protected:
    ObjectNameBox nameBox;
    CoordinateBox coordBox1, coordBox2;
};

/**
 * Dialog window to request data for a polygon
 */
class PolygonDialog : public Gtk::Dialog {
  public:
    PolygonDialog();

    std::string getName() { return nameBox.getName(); }
    CG::GObject::Coordinates getCoordinates() { return coordinates; }

  protected:
    ObjectNameBox nameBox;
    CG::GObject::Coordinates coordinates;
    void on_addCord_clicked();
    void addCoordinate(CG::Coordinate c);

    class PointsColumns : public Gtk::TreeModel::ColumnRecord{
      public:
        PointsColumns() { add(x); add(y); }

        Gtk::TreeModelColumn<float> x;
        Gtk::TreeModelColumn<float> y;
    };

    PointsColumns pointsColumns;
    Gtk::TreeView pointsTree;
    Glib::RefPtr<Gtk::ListStore> pointsModel;
    Gtk::Button addCoordBtn;
};

#endif
