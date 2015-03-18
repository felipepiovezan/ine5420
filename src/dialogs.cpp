#include "dialogs.h"

#define SPACING 5

using namespace std::placeholders;

// ==========================================================
// ObjectNameBox

ObjectNameBox::ObjectNameBox() {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(SPACING);

  label.set_label("Object name");
  pack_start(label, Gtk::PACK_SHRINK);
  pack_start(name, Gtk::PACK_EXPAND_WIDGET);
  label.show();
  name.show();
}

std::string ObjectNameBox::getName() {
  return name.get_text();
}

// ==========================================================
// CoordinateBox

CoordinateBox::CoordinateBox() {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(SPACING);

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
  float x, y = 0;
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
// PointDialog

PointDialog::PointDialog() {
  set_title("Point");
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  get_vbox()->pack_start(coordBox);
  coordBox.show();
}

// ==========================================================
// NamedPointDialog

NamedPointDialog::NamedPointDialog() {
  set_title("Point");
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(coordBox);

  nameBox.show();
  coordBox.show();
}

// ==========================================================
// LineDialog

LineDialog::LineDialog() {
  set_title("Line");
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

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
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  addCoordBtn.set_label("Add coordinate");
  addCoordBtn.signal_clicked().connect(sigc::mem_fun(*this, &PolygonDialog::on_addCord_clicked));

  pointsModel = Gtk::ListStore::create(pointsColumns);
	pointsTree.set_model(pointsModel);
  pointsTree.append_column("x", pointsColumns.x);
  pointsTree.append_column("y", pointsColumns.y);
  pointsTree.set_size_request(0, 150);

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(pointsTree);
  get_vbox()->pack_start(addCoordBtn);

  addCoordBtn.show();
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
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
  add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  get_vbox()->pack_start(coordBox);

  coordBox.labelX.set_label("dx");
  coordBox.labelY.set_label("dy");

  coordBox.show();
}
