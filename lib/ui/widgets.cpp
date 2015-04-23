#include "ui/widgets.h"

#include "ui/dialogs.h"

Grid::Grid() {
  set_border_width(5);
  set_row_spacing(5);
  set_column_spacing(5);
  set_row_homogeneous(true);
  set_column_homogeneous(true);
}

CoordinatesPanel::CoordinatesPanel() {
  addCoordBtn.set_label("Add coordinate");
  addCoordBtn.signal_clicked().connect(
    sigc::mem_fun(*this, &CoordinatesPanel::on_addCord_clicked));

  pointsModel = Gtk::ListStore::create(pointsColumns);
  pointsTree.set_model(pointsModel);
  pointsTree.append_column("x", pointsColumns.x);
  pointsTree.append_column("y", pointsColumns.y);
  pointsTree.append_column("z", pointsColumns.z);
  // TODO: try this: append_column_editable (https://developer.gnome.org/gtkmm-tutorial/stable/sec-treeview-examples.html.en#sec-editable-cells-example)
  pointsTree.set_size_request(0, 150);

  pack_start(pointsTree);
  pack_start(addCoordBtn);

  pointsTree.show();
  addCoordBtn.show();
}

void CoordinatesPanel::addCoordinate(CG::Coordinate c) {
  coordinates.push_back(c);
  Gtk::TreeModel::Row row = *(pointsModel->append());
  row[pointsColumns.x] = c.x;
  row[pointsColumns.y] = c.y;
  row[pointsColumns.z] = c.z;
}

void CoordinatesPanel::on_addCord_clicked() {
  PointDialog dialog;
  if (dialog.run()) {
    addCoordinate(dialog.getCoordinate());
  }
}
