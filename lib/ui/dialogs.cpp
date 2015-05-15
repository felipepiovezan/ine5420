#include "ui/dialogs.h"

#include <ctime>

// ==========================================================
// ObjectNameBox

ObjectNameBox::ObjectNameBox() {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(5);

  name.set_text(std::string("obj") + std::to_string(clock() % 100000));  // make a default name because we're too lazy to type

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
  labelZ.set_label("Z");

  entryX.set_width_chars(10);
  entryY.set_width_chars(10);
  entryZ.set_width_chars(10);

  pack_start(labelX, Gtk::PACK_SHRINK);
  pack_start(entryX, Gtk::PACK_SHRINK);
  pack_start(labelY, Gtk::PACK_SHRINK);
  pack_start(entryY, Gtk::PACK_SHRINK);
  pack_start(labelZ, Gtk::PACK_SHRINK);
  pack_start(entryZ, Gtk::PACK_SHRINK);

  labelX.show();
  entryX.show();
  labelY.show();
  entryY.show();
  labelZ.show();
  entryZ.show();
}

CG::Coordinate CoordinateBox::getCoordinate() {
  return CG::Coordinate(entryX.getValue(), entryY.getValue(), entryZ.getValue());
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
// ObjectDialog Dialog

ObjectDialog::ObjectDialog() : Dialog() {

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

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(filledCheckBtn);
  get_vbox()->pack_start(coordPanel);

  nameBox.show();
  filledCheckBtn.show();
  coordPanel.show();
}

// ==========================================================
// CurveDialog

CurveDialog::CurveDialog() {
  set_title("Curve");

  Gtk::RadioButton::Group group = bezierRB.get_group();
  splineRB.set_group(group);
  bezierRB.set_label("Bezier curve (uses blending function)");
  splineRB.set_label("Spline curve (uses forward distances)");

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(bezierRB);
  get_vbox()->pack_start(splineRB);
  get_vbox()->pack_start(coordPanel);

  nameBox.show();
  bezierRB.show();
  splineRB.show();
  coordPanel.show();
}

CG::GObject::Type CurveDialog::getCurveType() const {
  if (bezierRB.get_active()) {
    return CG::GObject::Type::BEZIER_CURVE;
  } else {
    return CG::GObject::Type::SPLINE_CURVE;
  }
}

// ==========================================================
// SurfaceDialog

SurfaceDialog::SurfaceDialog() {
  set_title("Surface");

  Gtk::RadioButton::Group group = bezierRB.get_group();
  splineRB.set_group(group);
  bezierRB.set_label("Bezier surface");
  splineRB.set_label("Spline surface");

  get_vbox()->pack_start(nameBox);
  get_vbox()->pack_start(bezierRB);
  get_vbox()->pack_start(splineRB);
  get_vbox()->pack_start(coordPanel);

  nameBox.show();
  bezierRB.show();
  splineRB.show();
  coordPanel.show();
}

CG::GSurface::SurfaceType SurfaceDialog::getType() const {
  if (bezierRB.get_active()) {
    return CG::GSurface::BEZIER; // TODO: changed to BEZIER_SURFACE type
  } else {
    return CG::GSurface::B_SPLINE; // TODO: changed to SPLINE_SURFACE type
  }
}

// ==========================================================
// TranslateDialog

TranslateDialog::TranslateDialog() {
  set_title("Translate Object");

  get_vbox()->pack_start(coordBox);

  coordBox.labelX.set_label("dx");
  coordBox.labelY.set_label("dy");
  coordBox.labelZ.set_label("dz");

  coordBox.show();
}

// ==========================================================
// ScaleDialog

ScaleDialog::ScaleDialog() {
  set_title("Scale Object");

  get_vbox()->pack_start(coordBox);

  coordBox.labelX.set_label("sx");
  coordBox.labelY.set_label("sy");
  coordBox.labelZ.set_label("sz");

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
  get_vbox()->pack_start(degreesGrid);

  xLabel.set_label("x rotation (degrees): ");
  yLabel.set_label("y rotation (degrees): ");
  zLabel.set_label("z rotation (degrees): ");

  xRotation.set_text("0");
  yRotation.set_text("0");
  zRotation.set_text("0");

  degreesGrid.attach(xLabel, 0, 0, 1, 1);
  degreesGrid.attach(xRotation, 1, 0, 1, 1);

  degreesGrid.attach(yLabel, 0, 1, 1, 1);
  degreesGrid.attach(yRotation, 1, 1, 1, 1);

  degreesGrid.attach(zLabel, 0, 2, 1, 1);
  degreesGrid.attach(zRotation, 1, 2, 1, 1);

  xLabel.show();
  xRotation.show();
  yLabel.show();
  yRotation.show();
  zLabel.show();
  zRotation.show();
  degreesGrid.show();
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
  centerCoordBox.labelZ.set_label("cz");
  centerBox.pack_start(centerCoordBox);

  centerBox.show();
  centerCoordBox.show();
  frame.show();
  objRB.show();;
  worldRB.show();
  coordRB.show();
}

bool RotateDialog::isAroundObjectCenterSelected() {
  return centerCoordBox.entryX.get_text().empty() && centerCoordBox.entryY.get_text().empty();
}

void RotateDialog::on_obj_rb_clicked() {
  centerCoordBox.entryX.set_text("");
  centerCoordBox.entryY.set_text("");
  centerCoordBox.entryZ.set_text("");
}

void RotateDialog::on_world_rb_clicked() {
  centerCoordBox.entryX.set_text("0");
  centerCoordBox.entryY.set_text("0");
  centerCoordBox.entryZ.set_text("0");
}

void RotateDialog::on_coord_rb_clicked() {
  centerCoordBox.entryX.set_text("0");
  centerCoordBox.entryY.set_text("0");
  centerCoordBox.entryZ.set_text("0");
  centerCoordBox.entryX.grab_focus();
}
