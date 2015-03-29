#ifndef INCLUDE_CG_CLIPPINGSTRATEGY_H_
#define INCLUDE_CG_CLIPPINGSTRATEGY_H_

#include "cg/GObject.h"

namespace CG{
	template <typename PointStrategy, typename LineStrategy, typename PolygonStrategy>
	class ClippingStrategy : private PointStrategy, private LineStrategy, private PolygonStrategy {
		using PointStrategy::clipPoint;
		using LineStrategy::clipLine;
		using PolygonStrategy::clipPolygon;
		public:
			bool clip(GPoint& p) {return clipPoint(p);}
			bool clip(GLine& l) {return clipLine(l);}
			bool clip(GPolygon& pol) {return clipPolygon(pol);}
	};

	class DoNothingPointClipping{
		protected:
			bool clipPoint(GPoint& p){ return true;}
	};

	class DoNothingLineClipping{
		protected:
			bool clipLine(GLine& l){ return true;}
	};

	class DoNothingPolygonClipping{
		protected:
			bool clipPolygon(GPolygon& pol) { return true; }
	};
}



#endif /* INCLUDE_CG_CLIPPINGSTRATEGY_H_ */
