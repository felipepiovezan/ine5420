#ifndef DIALOGS_H_
#define DIALOGS_H_

#include <gtkmm.h>
#include <string>
#include "GObject.h"
#include "MainWindow.h"

class ObjectNameBox : public Gtk::Box {
  public:
    ObjectNameBox();
    Gtk::Label label;
    Gtk::Entry name;

    std::string getName();
};

class CoordinateBox : public Gtk::Box {
  public:
    CoordinateBox();
    Gtk::Label labelX, labelY;
    Gtk::Entry entryX, entryY;

    CG::Coordinate getCoordinate();
};

class PointDialog : public Gtk::Dialog {
  public:
    typedef std::function<void (CG::Coordinate c, std::string name)> Callback;
    PointDialog(Callback callback);

    ObjectNameBox nameBox;
    CoordinateBox coordBox;

  protected:
    Callback callback;
    void on_response(int response);
};

#endif
