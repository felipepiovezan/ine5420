#include "ui/MainWindow.h"

#include "cg/Window.h"
#include "cg/DisplayFile.h"

MainWindow::MainWindow() :
	drawingCtx(),
	scene(drawingCtx),
	_toolbox(scene) {
		scene.addListener(_toolbox._objectsTreeView);

		init_examples();
		init_handlers();
		init_action_menu();

		// Layouting
		set_title("Computer Graphics Interative System");
		set_border_width(10);

		add(_mainBox);
		_mainBox.set_spacing(10);
		_mainBox.show();

		_mainBox.pack_start(_toolbox, Gtk::PACK_SHRINK);
		_toolbox.set_size_request(200, 0);
		_mainBox.pack_start(drawingCtx, Gtk::PACK_EXPAND_PADDING);
		drawingCtx.set_size_request(600, 600);

		set_resizable(false);

		_toolbox.show();
		drawingCtx.show();
}

void MainWindow::init_examples() {
	scene.createLine("Xaxis", CG::Color(1, 0, 0), CG::Coordinate(-1000, 0), CG::Coordinate(1000, 0));
	scene.createLine("Yaxis", CG::Color(0, 0, 1), CG::Coordinate(0, -1000), CG::Coordinate(0, 1000));

  init_leaf();
}

void MainWindow::init_handlers() {
  _toolbox._newPoint.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPoint));
  _toolbox._newLine.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newLine));
  _toolbox._newPolygon.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPolygon));

  _toolbox._zoomInBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::zoomIn));
  _toolbox._zoomOutBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::zoomOut));
  _toolbox._leftBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::left));
  _toolbox._rightBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::right));
  _toolbox._upBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::up));
  _toolbox._downBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::down));

  _toolbox._rotateLeftBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::rotateLeft));
  _toolbox._rotateRightBtn.signal_clicked().connect(sigc::mem_fun(scene, &CG::Scene::rotateRight));
}

void MainWindow::init_action_menu() {
	_actionGroup = Gtk::ActionGroup::create();
	_actionGroup->add(Gtk::Action::create("MenuFile", "File"));
	_actionGroup->add(Gtk::Action::create("MenuFileOpen", Gtk::Stock::OPEN, "Open..."), sigc::mem_fun(*this, &MainWindow::on_action_file_open));
	_actionGroup->add(Gtk::Action::create("MenuFileSave", Gtk::Stock::SAVE, "Save..."), sigc::mem_fun(*this, &MainWindow::on_action_file_save));

	_uiManager = Gtk::UIManager::create();
	_uiManager->insert_action_group(_actionGroup);
	add_accel_group(_uiManager->get_accel_group());

	Glib::ustring menuBarLayout =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='MenuFileOpen'/>"
    "      <menuitem action='MenuFileSave'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";

		_uiManager->add_ui_from_string(menuBarLayout);
		_mainBox.pack_start(*_uiManager->get_widget("/MenuBar"));
}

void MainWindow::on_newPoint() {
  NamedPointDialog pointDialog;
  if (pointDialog.run() == Gtk::RESPONSE_OK) {
    scene.createPoint(pointDialog.getName(), pointDialog.getColor(), pointDialog.getCoordinate());
  }
}

void MainWindow::on_newLine() {
  LineDialog lineDialog;
  if (lineDialog.run() == Gtk::RESPONSE_OK) {
		scene.createLine(lineDialog.getName(), lineDialog.getColor(), lineDialog.getCoordinate1(), lineDialog.getCoordinate2());
  }
}

void MainWindow::on_newPolygon() {
  PolygonDialog polygonDialog;
  if (polygonDialog.run() == Gtk::RESPONSE_OK) {
		scene.createPolygon(polygonDialog.getName(), polygonDialog.getColor(), polygonDialog.getCoordinates());
  }
}

void MainWindow::init_leaf(){
  CG::GObject::Coordinates c;
  c.push_back(CG::Coordinate(-1,-10));
  c.push_back(CG::Coordinate(0,-6));
  c.push_back(CG::Coordinate(-2,-7));
  c.push_back(CG::Coordinate(-3,-7));
  c.push_back(CG::Coordinate(-6,-6));
  c.push_back(CG::Coordinate(-5,-5));
  c.push_back(CG::Coordinate(-8,-3));
  c.push_back(CG::Coordinate(-7,-3));
  c.push_back(CG::Coordinate(-8,-1));
  c.push_back(CG::Coordinate(-8,1));
  c.push_back(CG::Coordinate(-6,0));
  c.push_back(CG::Coordinate(-5,0));
  c.push_back(CG::Coordinate(-3,-1));
  c.push_back(CG::Coordinate(-7,3));
  c.push_back(CG::Coordinate(-5,4));
  c.push_back(CG::Coordinate(-6,6));
  c.push_back(CG::Coordinate(-5,6));
  c.push_back(CG::Coordinate(-5,10));
  c.push_back(CG::Coordinate(-4,8));
  c.push_back(CG::Coordinate(-2,8));
  c.push_back(CG::Coordinate(-1,6));
  c.push_back(CG::Coordinate(0,8));
  c.push_back(CG::Coordinate(1,6));
  c.push_back(CG::Coordinate(1,2));
  c.push_back(CG::Coordinate(2,5));
  c.push_back(CG::Coordinate(3,5));
  c.push_back(CG::Coordinate(4,7));
  c.push_back(CG::Coordinate(5,5));
  c.push_back(CG::Coordinate(6,5));
  c.push_back(CG::Coordinate(5,2));
  c.push_back(CG::Coordinate(6,2));
  c.push_back(CG::Coordinate(6,1));
  c.push_back(CG::Coordinate(4,-2));
  c.push_back(CG::Coordinate(7,-2));
  c.push_back(CG::Coordinate(6,-4));
  c.push_back(CG::Coordinate(4,-5));
  c.push_back(CG::Coordinate(5,-6));
  c.push_back(CG::Coordinate(4,-7));
  c.push_back(CG::Coordinate(3,-7));
  c.push_back(CG::Coordinate(1,-6));
  c.push_back(CG::Coordinate(0,-6));
  c.push_back(CG::Coordinate(-1,-10));
	scene.createPolygon("leaf body", CG::Color(0, 1, 0), c);
}

void MainWindow::on_action_file_open() {
	Gtk::FileChooserDialog dialog("Choose file to open", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.add_button("Open", Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if (dialog.run() == Gtk::RESPONSE_OK) {
		ObjReader r(dialog.get_filename());
		int i=0;
		for(const auto &it : r.objects()){
			scene.addObject(std::string(dialog.get_filename()) + std::to_string(i), it);
			i++;
		}
	}
}

void MainWindow::on_action_file_save() {
	Gtk::FileChooserDialog dialog("Choose destination file", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.add_button("Save", Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if (dialog.run() == Gtk::RESPONSE_OK) {
		// TODO: save .obj file here
	}
}
