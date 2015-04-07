#include "ui/dialogs.h"

// ==========================================================
// ObjectNameBox

ObjectNameBox::ObjectNameBox() {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(5);

  label.set_label("Object name");
  pack_start(label, Gtk::PACK_SHRINK);
  pack_start(name, Gtk::PACK_EXPAND_WIDGET);
  pack_start(colorBtn, Gtk::PACK_SHRINK);
  label.show();
  name.show();
  colorBtn.show();
}

std::string ObjectNameBox::getName() {
  return name.get_text();
}

CG::Color ObjectNameBox::getColor() {
  Gdk::Color gdkColor = colorBtn.get_color();
  return CG::Color(gdkColor.get_red_p(), gdkColor.get_green_p(), gdkColor.get_blue_p());
}

// ==========================================================
// CoordinateBox

CoordinateBox::CoordinateBox() {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(5);

  labelX.set_label("X");
  labelY.set_label("Y");

  pack_start(labelX, Gtk::PACK_SHRINK);
  pack_start(entryX, Gtk::PACK_SHRINK);
  pack_start(labelY, Gtk::PACK_SHRINK);
  pack_start(entryY, Gtk::PACK_SHRINK);

  labelX.show();
  entryX.show();
  labelY.show();
  entryY.show();
}

CG::Coordinate CoordinateBox::getCoordinate() {
  double x, y = 0;
  std::stringstream buffer;

  buffer << entryX.get_text().raw();
  buffer >> x;
	buffer.clear();
  buffer << entryY.get_text().raw();
  buffer >> y;
	buffer.clear();

  return CG::Coordinate(x, y);
}


// ==========================================================
// Generic Dialog

Dialog::Dialog() {
  set_border_width(10);
  get_vbox()->set_spacing(5);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
  add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
}

// ==========================================================
// PointDialog

PointDialog::PointDialog() {
  set_title("Point");

  get_vbox()->pack_start(coordBox);
  coordBox.show();
}

// ==========================================================
// NamedPointDialog

NamedPointDialog::NamedPointDialog() {
  set_title("Point");

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(coordBox);

  nameBox.show();
  coordBox.show();
}

// ==========================================================
// LineDialog

LineDialog::LineDialog() {
  set_title("Line");

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(coordBox1);
  get_vbox()->pack_start(coordBox2);

  nameBox.show();
  coordBox1.show();
  coordBox2.show();
}

// ==========================================================
// PolygonDialog

PolygonDialog::PolygonDialog() {
  set_title("Polygon");

  filledCheckBtn.set_label("Filled polygon");
  addCoordBtn.set_label("Add coordinate");
  addCoordBtn.signal_clicked().connect(sigc::mem_fun(*this, &PolygonDialog::on_addCord_clicked));

  pointsModel = Gtk::ListStore::create(pointsColumns);
	pointsTree.set_model(pointsModel);
  pointsTree.append_column("x", pointsColumns.x);
  pointsTree.append_column("y", pointsColumns.y);
  pointsTree.set_size_request(0, 150);

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(filledCheckBtn);
  get_vbox()->pack_start(pointsTree);
  get_vbox()->pack_start(addCoordBtn);

  addCoordBtn.show();
  filledCheckBtn.show();
  nameBox.show();
  pointsTree.show();
}

void PolygonDialog::on_addCord_clicked() {
  PointDialog pointDialog;
  if (pointDialog.run() == Gtk::RESPONSE_OK) {
    addCoordinate(pointDialog.getCoordinate());
  }
}

void PolygonDialog::addCoordinate(CG::Coordinate c) {
  coordinates.push_back(c);
  Gtk::TreeModel::Row row = *(pointsModel->append());
	row[pointsColumns.x] = c.x;
	row[pointsColumns.y] = c.y;
}

// ==========================================================
// TranslateDialog

TranslateDialog::TranslateDialog() {
  set_title("Translate Object");

  get_vbox()->pack_start(coordBox);

  coordBox.labelX.set_label("dx");
  coordBox.labelY.set_label("dy");

  coordBox.show();
}

// ==========================================================
// ScaleDialog

ScaleDialog::ScaleDialog() {
  set_title("Scale Object");

  get_vbox()->pack_start(coordBox);

  coordBox.labelX.set_label("sx");
  coordBox.labelY.set_label("sy");

  coordBox.show();
}
// ==========================================================
// RotateDialog

RotateDialog::RotateDialog() {
  set_title("Rotate Object");
  init_degree_widgets();
  init_center_widgets();
  on_obj_rb_clicked();
}

void RotateDialog::init_degree_widgets() {
  degreesBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  degreesBox.set_spacing(5);
  degreesLabel.set_label("Degrees: ");
  get_vbox()->pack_start(degreesBox);

  degreesBox.pack_start(degreesLabel, Gtk::PACK_SHRINK);
  degreesBox.pack_start(degreesEntry, Gtk::PACK_EXPAND_WIDGET);

  degreesLabel.show();
  degreesEntry.show();
  degreesBox.show();
}

void RotateDialog::init_center_widgets() {
  centerBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
  centerBox.set_spacing(5);
  centerBox.set_border_width(5);
  frame.set_label("Rotation center");
  get_vbox()->pack_start(frame);
  frame.add(centerBox);

  Gtk::RadioButton::Group group = objRB.get_group();
  worldRB.set_group(group);
  coordRB.set_group(group);
  objRB.set_label("Object center");
  worldRB.set_label("World center");
  coordRB.set_label("Custom point");
  objRB.signal_clicked().connect(sigc::mem_fun(*this, &RotateDialog::on_obj_rb_clicked));
  worldRB.signal_clicked().connect(sigc::mem_fun(*this, &RotateDialog::on_world_rb_clicked));
  coordRB.signal_clicked().connect(sigc::mem_fun(*this, &RotateDialog::on_coord_rb_clicked));

  centerBox.pack_start(objRB);
  centerBox.pack_start(worldRB);
  centerBox.pack_start(coordRB);

  centerCoordBox.labelX.set_label("cx");
  centerCoordBox.labelY.set_label("cy");
  centerBox.pack_start(centerCoordBox);

  centerBox.show();
  centerCoordBox.show();
  frame.show();
  objRB.show();;
  worldRB.show();
  coordRB.show();
}

double RotateDialog::getRotation() {
  double rotation = 0;
  std::stringstream buffer;

  buffer << degreesEntry.get_text().raw();
  buffer >> rotation;
  buffer.clear();

  return rotation;
}

bool RotateDialog::isAroundObjectCenterSelected() {
  return centerCoordBox.entryX.get_text().empty() && centerCoordBox.entryY.get_text().empty();
}

void RotateDialog::on_obj_rb_clicked() {
  centerCoordBox.entryX.set_text("");
  centerCoordBox.entryY.set_text("");
}

void RotateDialog::on_world_rb_clicked() {
  centerCoordBox.entryX.set_text("0");
  centerCoordBox.entryY.set_text("0");
}

void RotateDialog::on_coord_rb_clicked() {
  centerCoordBox.entryX.set_text("0");
  centerCoordBox.entryY.set_text("0");
  centerCoordBox.entryX.grab_focus();
}
