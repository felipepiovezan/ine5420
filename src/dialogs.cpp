#include "dialogs.h"

#define SPACING 5

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

PointDialog::PointDialog(Callback callback) : callback(callback) {
  set_title("Point");
  set_border_width(10);
  get_vbox()->set_spacing(SPACING);

  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  signal_response().connect(sigc::mem_fun(*this, &PointDialog::on_response));

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(coordBox);

  nameBox.show();
  coordBox.show();
}

void PointDialog::on_response(int response) {
  if(response == Gtk::RESPONSE_OK) {
    callback(coordBox.getCoordinate(), nameBox.getName());
  }
}
