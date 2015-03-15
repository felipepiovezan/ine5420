#ifndef __VIEWPORT
#define __VIEWPORT

#include <gtkmm/drawingarea.h>
#include "Window.h"
#include "DisplayFile.h"
#include "GObject.h"

class Viewport : public Gtk::DrawingArea {
	private:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
		void drawObject(const CG::GObject &obj, const Cairo::RefPtr<Cairo::Context>& ctx);

		int transformX(int x);
		int transformY(int y);
		
		CG::Window _window;
		CG::DisplayFile _displayFile;
	
	public:
		//constructors
		Viewport() = default;
		Viewport(CG::Window window, CG::DisplayFile dfile);
	
		//Window methods
		void setWindowZoom(float factor) {_window.scaleFactor(factor);}
		void setWindowDx(float dx) {_window.dx(dx);}
		void setWindowDy(float dy) {_window.dy(dy);}

		//getters
		const CG::Window& window() const {return _window;}
		const CG::DisplayFile& displayFile() const {return _displayFile;}

		//setters
		void window(const CG::Window& newWindow){ _window = newWindow;}
		void displayFile(const CG::DisplayFile& newDisplayFile){ _displayFile = newDisplayFile;}
};

#endif
