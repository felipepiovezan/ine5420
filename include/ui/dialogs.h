#ifndef DIALOGS_H_
#define DIALOGS_H_

#include <gtkmm.h>
#include <string>

#include "cg/GObject.h"
#include "ui/MainWindow.h"

/**
 * Custom widget to request an object name and its color
 */
class ObjectNameBox : public Gtk::Box {
  public:
    ObjectNameBox();
    Gtk::Label label;
    Gtk::Entry name;
    Gtk::ColorButton colorBtn;

    std::string getName();
    CG::Color getColor();
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
 * Generic dialog to be extended by all application dialogs
 */
class Dialog : public Gtk::Dialog {
  public:
    Dialog();
};

/**
 * Dialog window to request a coordinate
 */
class PointDialog : public Dialog {
  public:
    PointDialog();
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    CoordinateBox coordBox;
};

/**
 * Dialog window to request a coordinate and the point name
 */
class NamedPointDialog : public Dialog {
  public:
    NamedPointDialog();
    std::string getName() { return nameBox.getName(); }
    CG::Color getColor() { return nameBox.getColor(); }
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    ObjectNameBox nameBox;
    CoordinateBox coordBox;
};

/**
 * Dialog window to request data for a Line
 */
class LineDialog : public Dialog {
  public:
    LineDialog();

    std::string getName() { return nameBox.getName(); }
    CG::Color getColor() { return nameBox.getColor(); }
    CG::Coordinate getCoordinate1() { return coordBox1.getCoordinate(); }
    CG::Coordinate getCoordinate2() { return coordBox2.getCoordinate(); }

  protected:
    ObjectNameBox nameBox;
    CoordinateBox coordBox1, coordBox2;
};

/**
 * Dialog window to request data for a polygon
 */
class PolygonDialog : public Dialog {
  public:
    PolygonDialog();

    std::string getName() { return nameBox.getName(); }
    CG::Color getColor() { return nameBox.getColor(); }
    CG::GObject::Coordinates getCoordinates() { return coordinates; }

  protected:
    ObjectNameBox nameBox;
    CG::GObject::Coordinates coordinates;
    void on_addCord_clicked();
    void addCoordinate(CG::Coordinate c);

    class PointsColumns : public Gtk::TreeModel::ColumnRecord {
      public:
        PointsColumns() { add(x); add(y); }

        Gtk::TreeModelColumn<double> x;
        Gtk::TreeModelColumn<double> y;
    };

    PointsColumns pointsColumns;
    Gtk::TreeView pointsTree;
    Glib::RefPtr<Gtk::ListStore> pointsModel;
    Gtk::Button addCoordBtn;
};

/**
 * Dialog Window for Object Translation
 */
class TranslateDialog : public Dialog {
  public:
    TranslateDialog();
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    CoordinateBox coordBox;
};

/**
 * Dialog Window for Object Scaling
 */
class ScaleDialog : public Dialog {
  public:
    ScaleDialog();
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    CoordinateBox coordBox;
};

/**
 * Dialog Window for Object Scaling
 */
class RotateDialog : public Dialog {
  public:
    RotateDialog();
    CG::Coordinate getRotationCenter() { return centerCoordBox.getCoordinate(); }
    double getRotation();
    bool isAroundObjectCenterSelected();

  protected:
    void init_degree_widgets();
    void init_center_widgets();

    void on_obj_rb_clicked();
    void on_world_rb_clicked();
    void on_coord_rb_clicked();

    Gtk::Box degreesBox;
    Gtk::Label degreesLabel;
    Gtk::Entry degreesEntry;

    Gtk::Frame frame;
    CoordinateBox centerCoordBox;
    Gtk::Box centerBox;
    Gtk::RadioButton objRB, worldRB, coordRB;
};


#endif
