#ifndef WIDGETS_H_
#define WIDGETS_H_

#include <vector>
#include <string>
#include <gtkmm.h>
#include "cg/objects.h"

/**
 * The default application grid
 */
class Grid : public Gtk::Grid {
 public:
  Grid();
};

/**
 * A panel for managing a collection of coordinates
 */
class CoordinatesPanel : public Gtk::VBox {
 public:
  Gtk::Button addCoordBtn;

  class PointsColumns : public Gtk::TreeModel::ColumnRecord {
   public:
    PointsColumns() { add(x); add(y); add(z); }

    Gtk::TreeModelColumn<double> x;
    Gtk::TreeModelColumn<double> y;
    Gtk::TreeModelColumn<double> z;
  };
  PointsColumns pointsColumns;
  Gtk::TreeView pointsTree;
  Glib::RefPtr<Gtk::ListStore> pointsModel;

  CoordinatesPanel();
  void addCoordinate(CG::Coordinate c);
  std::vector<CG::Coordinate> getCoordinates() { return coordinates; }

 protected:
  std::vector<CG::Coordinate> coordinates;
  void on_addCord_clicked();
};

#endif
