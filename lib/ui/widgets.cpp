#include "ui/widgets.h"

#include <ctime>
#include "ui/dialogs.h"

Grid::Grid() {
  set_border_width(5);
  set_row_spacing(5);
  set_column_spacing(5);
  set_row_homogeneous(true);
  set_column_homogeneous(true);
}

double NumericEntry::getValue() {
  double value = 0;
  std::stringstream buffer;

  buffer << get_text().raw();
  buffer >> value;
  buffer.clear();

  return value;
}

CoordinatesPanel::CoordinatesPanel() {
  addCoordBtn.set_label("Add coordinate");
  addCoordBtn.signal_clicked().connect(
    sigc::mem_fun(*this, &CoordinatesPanel::on_addCord_clicked));

  pointsModel = Gtk::ListStore::create(pointsColumns);
  pointsTree.set_model(pointsModel);
  pointsTree.append_column_numeric_editable("x", pointsColumns.x, "%f");
  pointsTree.append_column_numeric_editable("y", pointsColumns.y, "%f");
  pointsTree.append_column_numeric_editable("z", pointsColumns.z, "%f");

  scrolledWindow.set_size_request(0, 300);
  scrolledWindow.add(pointsTree);

  pack_start(scrolledWindow);
  pack_start(addCoordBtn);

  pointsTree.show();
  addCoordBtn.show();
  scrolledWindow.show();
}

void CoordinatesPanel::addCoordinate(CG::Coordinate c) {
  Gtk::TreeModel::Row row = *(pointsModel->append());
  row[pointsColumns.x] = c.x;
  row[pointsColumns.y] = c.y;
  row[pointsColumns.z] = c.z;
}

void CoordinatesPanel::on_addCord_clicked() {
  addCoordinate(CG::Coordinate((clock() % 10), (clock() % 10), (clock() % 10)));
}

std::vector<CG::Coordinate> CoordinatesPanel::getCoordinates() {
  std::vector<CG::Coordinate> coordinates;

  for (auto iter : pointsModel->children()) {
    Gtk::TreeModel::Row row = *iter;
    double x = row[pointsColumns.x];
    double y = row[pointsColumns.y];
    double z = row[pointsColumns.z];
    coordinates.emplace_back(x, y, z);
  }

  return coordinates;
}
