#ifndef INCLUDE_CG_CLIPPINGSTRATEGY_H_
#define INCLUDE_CG_CLIPPINGSTRATEGY_H_

#include "cg/GObject.h"

namespace CG{
	typedef struct {
		double minX, maxX, minY, maxY;
	} ClippingRect;

	template <typename PointStrategy, typename LineStrategy, typename PolygonStrategy>
	class ClippingStrategy : private PointStrategy, private LineStrategy, private PolygonStrategy {
		using PointStrategy::clipPoint;
		using LineStrategy::clipLine;
		using PolygonStrategy::clipPolygon;
		public:
			bool clip(GPoint& p, const ClippingRect& rect) {return clipPoint(p, rect);}
			bool clip(GLine& l, const ClippingRect& rect) {return clipLine(l, rect);}
			bool clip(GPolygon& pol, const ClippingRect& rect) {return clipPolygon(pol, rect);}
	};

	class SimplePointClipping {
		protected:
			bool clipPoint(GPoint& p, const ClippingRect& rect);
	};

	/**
	 * Liang-Barsky Line Clipping
	 */
	class LBLineClipping{
		protected:
			bool clipLine(GLine& l, const ClippingRect& rect);
	};

	class DoNothingPolygonClipping{
		protected:
			bool clipPolygon(GPolygon& pol, const ClippingRect& rect) { return true; }
	};
}



#endif /* INCLUDE_CG_CLIPPINGSTRATEGY_H_ */
