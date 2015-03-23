#ifndef __VIEWPORT
#define __VIEWPORT

#include <gtkmm/drawingarea.h>
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/GObject.h"
#include <cassert>


class Viewport : public Gtk::DrawingArea {
	private:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
		void drawObject(const CG::GObject &obj, const Cairo::RefPtr<Cairo::Context>& ctx);

		double transformX(double x);
		double transformY(double y);

		CG::Window* _window;
		CG::DisplayFile* _displayFile;

	public:
		Viewport(CG::Window* window, CG::DisplayFile* dfile);
		void redraw() { queue_draw(); }

		const CG::DisplayFile* displayFile(){ return _displayFile;}

		//methods called by the gui, transformations on objects
		void applyTranslation(const std::string &name, double dx, double dy);
		void applyScaling(const std::string &name, double sx, double xy);
		void applyRotation(const std::string &name, double theta, const CG::Coordinate& rotationCenter);

		//methods called by the gui, transformations on the window
		void changeWindowZoom(double step);
		void changeWindowPosition(double sx, double sy);
		void rotateWindow(double theta);

};

#endif
