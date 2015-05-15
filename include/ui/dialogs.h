#ifndef DIALOGS_H_
#define DIALOGS_H_

#include <gtkmm.h>
#include <string>

#include "cg/objects.h"
#include "ui/widgets.h"
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
    Gtk::Label labelX, labelY, labelZ;
    NumericEntry entryX, entryY, entryZ;

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
 * Generic dialog for object creation or modification
 */
class ObjectDialog : public Dialog {
 public:
  ObjectDialog();

  virtual std::string getName() { return nameBox.getName(); }
  virtual CG::Decoration getDecoration() {
    CG::Decoration decoration;
    decoration.setLineColor(nameBox.getColor());
    return decoration;
  }

 protected:
  ObjectNameBox nameBox;
};

/**
 * Dialog window to request a coordinate and the point name
 */
class NamedPointDialog : public ObjectDialog {
  public:
    NamedPointDialog();
    CG::Coordinate getCoordinate() { return coordBox.getCoordinate(); }

  protected:
    CoordinateBox coordBox;
};

/**
 * Dialog window to request data for a Line
 */
class LineDialog : public ObjectDialog {
  public:
    LineDialog();
    CG::Coordinate getCoordinate1() { return coordBox1.getCoordinate(); }
    CG::Coordinate getCoordinate2() { return coordBox2.getCoordinate(); }

  protected:
    CoordinateBox coordBox1, coordBox2;
};

/**
 * Dialog window to request data for a polygon
 */
class PolygonDialog : public ObjectDialog {
  public:
    PolygonDialog();

    CG::GObject::Coordinates getCoordinates() { return coordPanel.getCoordinates(); }
    CG::Decoration getDecoration() {
      CG::Decoration decoration;
      decoration.setLineColor(nameBox.getColor());
      if (filledCheckBtn.get_active()) { //  TODO: create a ColorButton for fillColor
        decoration.setFillColor(nameBox.getColor());
      }
      return decoration;
    }

  protected:
    Gtk::CheckButton filledCheckBtn;
    CoordinatesPanel coordPanel;
};

/**
 * Dialog window to request data for a polygon
 */
class CurveDialog : public ObjectDialog {
  public:
    CurveDialog();
    CG::GObject::Coordinates getCoordinates() { return coordPanel.getCoordinates(); }
    CG::GObject::Type getCurveType() const;

  protected:
    CoordinatesPanel coordPanel;
    Gtk::RadioButton bezierRB, splineRB;
};

/**
 * Dialog window to request data for a surface
 */
class SurfaceDialog : public ObjectDialog {
  public:
    SurfaceDialog();
    CG::GObject::Coordinates getCoordinates() { return coordPanel.getCoordinates(); }
    CG::GSurface::SurfaceType getType() const;

  protected:
    CoordinatesPanel coordPanel;
    Gtk::RadioButton bezierRB, splineRB;
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
    double getXRotation() { return xRotation.getValue(); }
    double getYRotation() { return yRotation.getValue(); }
    double getZRotation() { return zRotation.getValue(); }
    bool isAroundObjectCenterSelected();

  protected:
    void init_degree_widgets();
    void init_center_widgets();

    void on_obj_rb_clicked();
    void on_world_rb_clicked();
    void on_coord_rb_clicked();

    Grid degreesGrid;
    Gtk::Label xLabel, yLabel, zLabel;
    NumericEntry xRotation, yRotation, zRotation;

    Gtk::Frame frame;
    CoordinateBox centerCoordBox;
    Gtk::Box centerBox;
    Gtk::RadioButton objRB, worldRB, coordRB;
};

#endif
