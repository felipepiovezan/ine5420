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
			bool clip(GPoint& p, ClippingRect& rect) {return clipPoint(p, rect);}
			bool clip(GLine& l, ClippingRect& rect) {return clipLine(l, rect);}
			bool clip(GPolygon& pol, ClippingRect& rect) {return clipPolygon(pol, rect);}
	};

	class SimplePointClipping {
		protected:
			bool clipPoint(GPoint& p, ClippingRect& rect);
	};

	class DoNothingLineClipping{
		protected:
			bool clipLine(GLine& l, ClippingRect& rect){ return true;}
	};

	class DoNothingPolygonClipping{
		protected:
			bool clipPolygon(GPolygon& pol, ClippingRect& rect) { return true; }
	};
}



#endif /* INCLUDE_CG_CLIPPINGSTRATEGY_H_ */
