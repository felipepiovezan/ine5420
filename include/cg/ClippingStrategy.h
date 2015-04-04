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

	class LBLineClipping{
		protected:
			bool clipLine(GLine& l, const ClippingRect& rect);
	};

	class NLNLineClipping{
		protected:
			bool clipLine(GLine& l, const ClippingRect& rect);
		private:
			inline void leftcolumn(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void centrecolumn(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void topleftcorner(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void leftedge(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void leftbottomregion(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&, const double &,const double &,const double &);
			inline void p2bottom(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void inside(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
			inline void p2left(const double &,const double &,const double &,const double &,double &,double &,double &,double &);
			inline void p2lefttop(const double &,const double &,const double &,const double &,double &,double &,double &,double &);
	};

	class SutherlandHodgmanPolygonClipping{
		protected:
			bool clipPolygon(GPolygon& pol, const ClippingRect& rect);
	};

	class DoNothingPolygonClipping{
		protected:
			bool clipPolygon(GPolygon& pol, const ClippingRect& rect) { return true; }
	};

	class DoNothingLineClipping{
		protected:
				bool clipLine(GLine& l, const ClippingRect& rect){return true;}
	};

}



#endif /* INCLUDE_CG_CLIPPINGSTRATEGY_H_ */
