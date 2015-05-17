#include "ui/MainWindow.h"

#include <gdk/gdkkeysyms.h>

MainWindow::MainWindow() :
	_world(new CG::World()),
	_window(0, 0, -5, 30, 30),
	_viewport(_window, _world),
	_toolbox(_world) {
		_world->addListener(_viewport);
		_world->addListener(_toolbox._objectsTreeView);

		init_examples();
		init_handlers();
		init_action_menu();

    tool = std::shared_ptr<CG::Tool>(new CG::HandTool(_viewport)); // TODO: make better management for another tools

    // Setup events
    add_events(Gdk::KEY_PRESS_MASK |
               Gdk::POINTER_MOTION_MASK |
               Gdk::BUTTON_PRESS_MASK |
               Gdk::SCROLL_MASK);

		// Layouting
		set_title("Computer Graphics Interactive System");
		set_border_width(10);

		add(_mainBox);
		_mainBox.set_spacing(10);
		_mainBox.show();

		_mainBox.pack_start(_toolbox, Gtk::PACK_SHRINK);
		_toolbox.set_size_request(200, 0);
		_mainBox.pack_start(_viewport, Gtk::PACK_EXPAND_PADDING);
		_viewport.set_size_request(1000, 1000);

		set_resizable(false);

		_toolbox.show();
		_viewport.show();
}

void MainWindow::init_examples() {
  // Rectangle
  CG::GObject::Coordinates c;
  c.push_back(CG::Coordinate(-8, -12));
  c.push_back(CG::Coordinate(-8, 12));
  c.push_back(CG::Coordinate(8, 12));
  c.push_back(CG::Coordinate(8, -12));
  CG::Decoration decoration;
  decoration.setLineColor(CG::Color(0, 1, 0));
  _world->createPolygon("rectangle", decoration, c);

  // Bezier 3 exmaple
  c.clear();
  c.emplace_back(0, 0);
  c.emplace_back(1, 1);
  c.emplace_back(2, 2);
  c.emplace_back(2, -1);
  c.emplace_back(4, -1);
  c.emplace_back(4, -4);
  c.emplace_back(2, -5);
  decoration.setLineColor(CG::Color(.3, .5, .8));
  decoration.setLineWidth(3.0);
  _world->createBezierCurve("curve3", decoration, c);

  // Leaf
  init_leaf();

  //surface exmaple:
  c.clear();
  c.emplace_back(-1, 3, 1);
  c.emplace_back(0, 3, 1);
  c.emplace_back(1, 3, 1);
  c.emplace_back(2, 3, 1);

  c.emplace_back(-1, 3, 2);
  c.emplace_back(0, -2, 2);
  c.emplace_back(1, -2, 2);
  c.emplace_back(2, 3, 2);

  c.emplace_back(-1, 3, 3);
  c.emplace_back(0, -2, 3);
  c.emplace_back(1, -2, 3);
  c.emplace_back(2, 3, 3);

  c.emplace_back(-1, 3, 4);
  c.emplace_back(0, 3, 4);
  c.emplace_back(1, 3, 4);
  c.emplace_back(2, 3, 4);
  _world->createBezierSurface("surfaceProfessor", decoration, c);

//
//  // Bezier example
//  c.clear();
//  c.push_back(CG::Coordinate(0, 0));
//  c.push_back(CG::Coordinate(0, 6));
//  c.push_back(CG::Coordinate(7, 8));
//  c.push_back(CG::Coordinate(10, 8));
//  decoration.setLineColor(CG::Color(.3, .5, .8));
//  decoration.setLineWidth(3.0);
//  _world->createBezierCurve("curve1", decoration, c);
//
//  // Bezier 2 example
//  c.clear();
//  c.push_back(CG::Coordinate(-1, -1));
//  c.push_back(CG::Coordinate(-3, -6));
//  c.push_back(CG::Coordinate(-7, -8));
//  c.push_back(CG::Coordinate(-7, -8));
//  c.push_back(CG::Coordinate(-10, -7));
//  c.push_back(CG::Coordinate(-3, -5));
//  c.push_back(CG::Coordinate(-10, -7));
//  decoration.setLineColor(CG::Color(.5, .8, .3));
//  decoration.setLineWidth(3.0);
//  _world->createBezierCurve("curve2", decoration, c);
//
//  // Spline example
//  c.clear();
//  c.push_back(CG::Coordinate(5, 0));
//  c.push_back(CG::Coordinate(0, -5));
//  c.push_back(CG::Coordinate(-5, 0));
//  c.push_back(CG::Coordinate(0, 5));
//  c.push_back(CG::Coordinate(5, 0));
//  c.push_back(CG::Coordinate(0, -5));
//  c.push_back(CG::Coordinate(-5, 0));
//  decoration.setLineColor(CG::Color(.8, .1, .3));
//  decoration.setLineWidth(3.0);
//  _world->createSplineCurve("curve3", decoration, c);
//
//  // Spline 2 example
//  c.clear();
//  c.push_back(CG::Coordinate(-6, -4));
//  c.push_back(CG::Coordinate(-4, -4));
//  c.push_back(CG::Coordinate(-2, -4));
//  c.push_back(CG::Coordinate(0, 0));
//  c.push_back(CG::Coordinate(2, -4));
//  c.push_back(CG::Coordinate(4, -4));
//  c.push_back(CG::Coordinate(6, -4));
//  decoration.setLineColor(CG::Color(.8, .1, .99));
//  decoration.setLineWidth(3.0);
//  _world->createSplineCurve("curve4", decoration, c);
//
//  // Man
//  _world->addObject("zBasicMan", ObjReader("./ObjTestFiles/basicman.obj").objects());
}

void MainWindow::init_handlers() {
  _toolbox._newPoint.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPoint));
  _toolbox._newLine.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newLine));
  _toolbox._newPolygon.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newPolygon));
  _toolbox._newCurve.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newCurve));
  _toolbox._newSurface.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_newSurface));

  _toolbox._zoomInBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::zoomIn));
  _toolbox._zoomOutBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::zoomOut));
  _toolbox._leftBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::left));
  _toolbox._rightBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::right));
  _toolbox._upBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::up));
  _toolbox._downBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::down));

  _toolbox._rotateLeftBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::rotateLeft));
  _toolbox._rotateRightBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::rotateRight));

  _toolbox._bendForwardBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::bendForwards));
  _toolbox._bendBackwardBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::bendBackwards));
  _toolbox._bendLeftBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::bendLeft));
  _toolbox._bendRightBtn.signal_clicked().connect(sigc::mem_fun(_viewport, &CG::Viewport::bendRight));
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
  NamedPointDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    _world->createPoint(dialog.getName(), dialog.getDecoration(), dialog.getCoordinate());
  }
}

void MainWindow::on_newLine() {
  LineDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
		_world->createLine(dialog.getName(), dialog.getDecoration(), dialog.getCoordinate1(), dialog.getCoordinate2());
  }
}

void MainWindow::on_newPolygon() {
  PolygonDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
		_world->createPolygon(dialog.getName(), dialog.getDecoration(), dialog.getCoordinates());
  }
}

void MainWindow::on_newCurve() {
  CurveDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    try {
      if (dialog.getCurveType() == CG::GObject::BEZIER_CURVE) {
      _world->createBezierCurve(dialog.getName(), dialog.getDecoration(), dialog.getCoordinates());
      } else {
        _world->createSplineCurve(dialog.getName(), dialog.getDecoration(), dialog.getCoordinates());
      }
    } catch(CGException& e) {
      alert(e);
    }
  }
}

void MainWindow::on_newSurface() {
  SurfaceDialog dialog;
  if (dialog.run() == Gtk::RESPONSE_OK) {
    try {
        if (dialog.getType() == CG::GSurface::BEZIER) {
        _world->createBezierSurface(dialog.getName(), dialog.getDecoration(), dialog.getCoordinates());
        } else {
          _world->createSplineSurface(dialog.getName(), dialog.getDecoration(), dialog.getCoordinates());
        }
    } catch(CGException& e) {
      alert(e);
    }
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
  CG::Decoration decoration;
  decoration.setLineColor(CG::Color(0, 1, 0));
  decoration.setFillColor(CG::Color(0, 1, 0));
  _world->createPolygon("leaf", decoration, c);
	_world->scaleObject("leaf", 0.1,0.1, 1);
	_world->translateObject("leaf", 4.3, 6, 0);
	_world->rotateObject("leaf", 0, 0, 30);
}

void MainWindow::on_action_file_open() {
	Gtk::FileChooserDialog dialog("Choose file to open", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.add_button("Open", Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if (dialog.run() == Gtk::RESPONSE_OK) {
		ObjReader r(dialog.get_filename());
		std::cout << "read an object with " << r.object()->coordinates().size() << " points and "<< r.object()->faceList().size() << " faces" << std::endl;
    std::string basename = dialog.get_filename();
    basename.erase(0, basename.find_last_of("/") + 1); // get just the filename (erase the path)
		_world->addObject(basename, r.object());
	}
}

void MainWindow::on_action_file_save() {
	Gtk::FileChooserDialog dialog("Choose destination file", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.add_button("Save", Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if (dialog.run() == Gtk::RESPONSE_OK) {
		ObjWriter(dialog.get_filename()).writeObjects(_world->getObjects());
	}
}

bool MainWindow::on_key_press_event(GdkEventKey* event) {
	// If control is pressed
	if (event->state & GDK_CONTROL_MASK) {
		switch(event->keyval) {
			// Action menu shortcuts
			case GDK_KEY_o:
				on_action_file_open();
				break;
			case GDK_KEY_s:
				on_action_file_save();
				break;
		}
	} else { // No modifier pressed
		switch(event->keyval) {
			// Window translation
			case GDK_KEY_Up:
				_viewport.up();
				break;
			case GDK_KEY_Down:
				_viewport.down();
				break;
			case GDK_KEY_Left:
				_viewport.left();
				break;
			case GDK_KEY_Right:
				_viewport.right();
				break;

			// Window zoom
			case GDK_KEY_plus:
			case GDK_KEY_equal:
				_viewport.zoomIn();
				break;
			case GDK_KEY_minus:
				_viewport.zoomOut();
				break;
		}
	}

	return false;
}

bool MainWindow::on_scroll_event(GdkEventScroll* event) {
  if (event->x > _toolbox.get_width()) {
    if (event->direction == GDK_SCROLL_UP) {
      _viewport.zoomIn();
    } else if (event->direction == GDK_SCROLL_DOWN) {
      _viewport.zoomOut();
    }
  }

  return false;
}

/**
 * Fired when mouse is pressed (any button)
 */
bool MainWindow::on_button_press_event(GdkEventButton* event) {
  tool->init(event->x, event->y);
  return false;
}

/**
 * Fired when mouse is released (any button)
 */
bool MainWindow::on_button_release_event(GdkEventButton* event) {
  tool->end(event->x, event->y);
  return false;
}

/**
 * Fired when mouse is moved
 */
bool MainWindow::on_motion_notify_event(GdkEventMotion* event) {
  if (event->state & GDK_BUTTON1_MASK) {
    tool->update(event->x, event->y);
  }
  return false;
}

void MainWindow::alert(CGException& e) {
  Gtk::MessageDialog alert(e.what());
  alert.run();
}
