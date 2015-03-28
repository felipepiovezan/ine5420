#include "cg/Viewport.h"

namespace CG {

 Coordinate Viewport::transformCoordinate(const Coordinate& c) const {
   int width = getWidth();
   int height = getHeight();
   double x = width * (c.x - _window.xmin()) / (_window.xmax() - _window.xmin());
   double y = height * (1 - ((c.y - _window.ymin()) / (_window.ymax() - _window.ymin())));
   return Coordinate(x, y);
 }

 GObject::Coordinates Viewport::transformCoordinates(GObject::Coordinates coords) const {
   CG::GObject::Coordinates vwCoordinates;
   for (auto &c : coords) {
     vwCoordinates.push_back(transformCoordinate(c));
   }

   return vwCoordinates;
 }

	void Viewport::changeWindowZoom(double step){
		double width = _window.width();
		double height = _window.height();
		if(_window.zoom(step)){
			_window.updateMatrix();
			applyTransformation(Transformation::newScaling(width/(width+step), height/(height+step)));
			redraw();
		}
	}

	void Viewport::changeWindowPosition(double sx, double sy){
		_window.move(sx, sy);
		_window.updateMatrix();
		applyTransformation(Transformation::newTranslation(sx/_window.width(), sy/_window.height()));
		redraw();
	}

	void Viewport::rotateWindow(double theta){
		_window.rotate(Transformation::toRadians(theta));
		_window.updateMatrix();
		applyTransformation(Transformation::newRotationAroundOrigin(Transformation::toRadians(theta)));
		redraw();
	}

	void Viewport::onWorldChange(const DisplayFile& worldObjects){
		//TODO: improve this, only update the objects that changed.
		_windowObjects = worldObjects;
		applyTransformation(_window.wo2wiMatrix());
		redraw();
	}

	void Viewport::applyTransformation(const Transformation &t){
		for(auto &obj : _windowObjects.objects())
			obj.second.transform(t);
	}

}
