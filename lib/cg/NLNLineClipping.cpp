/*
 * Implementation as described by the authors in the original paper:
 * Tina M. Nicholl, D. T. Lee, Robin A. Nicholl (1987).
 * "An efficient new algorithm for 2-D line clipping: Its development and analysis". SIGGRAPH '87: 253–262.
 * Avaiable at: http://dl.acm.org/citation.cfm?id=37432
 */

#include "cg/ClippingStrategy.h"
#include <iostream>

namespace CG{
  	  #define rotate90c(x,y) {double __t=x; x=y; y=-__t;}
  	  #define rotate180c(x,y) x=-x; y=-y;
  	  #define rotate270c(x,y) {double __t=x; x=-y; y=__t;}
  	  #define reflectxminusy(x,y) {double __t=x; x=-y; y=-__t;}
  	  #define reflectxaxis(x,y) y=-y;

	  bool NLNLineClipping::clipLine(GLine& l, const ClippingRect& rect){
		  const double &xleft = rect.minX,
				  &xright = rect.maxX,
				  &ybottom = rect.minY,
				  &ytop = rect.maxY;
		  double &x1 = l.coordinates()[0].x,
				  &y1 = l.coordinates()[0].y,
				  &x2 = l.coordinates()[1].x,
				  &y2 = l.coordinates()[1].y;
		  bool display;
		  if(x1 < xleft){
			  leftcolumn(xleft, ytop, xright, ybottom,
					  	  	  	  x1,y1,x2,y2,display);
		  }
		  else if(x1 > xright){
			  rotate180c(x1,y1); rotate180c(x2,y2);
			  leftcolumn(-xright, -ybottom, -xleft, -ytop,
					  	  	  	  x1,y1,x2,y2,display);
			  rotate180c(x1,y1); rotate180c(x2,y2);

		  }
		  else{
			  centrecolumn(xleft, ytop, xright, ybottom,
					  	  	  	  x1,y1,x2,y2,display);
		  }
		  return display;
	  }

	  void NLNLineClipping::leftcolumn(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
			  double &x1,double &y1,double &x2,double &y2, bool &display){
		  if(x2 < xleft) display = false;
		  else if(y1 > ytop){
			  topleftcorner(xleft, ytop, xright, ybottom,
					  x1, y1, x2, y2, display);
		  }
		  else if(y1 < ybottom){
			  reflectxaxis(x1, y1); reflectxaxis (x2, y2);
			  topleftcorner(xleft, -ybottom, xright, -ytop,
					  x1, y1, x2, y2, display);
			  reflectxaxis(x1, y1); reflectxaxis (x2, y2)
		  }
		  else{
			  leftedge(xleft, ytop, xright, ybottom,
					  x1, y1, x2, y2, display);
		  }
	  }
	  void NLNLineClipping::topleftcorner(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
			  double &x1,double &y1,double &x2,double &y2, bool &display){
		  if(y2 > ytop) display = false;
		  else {
			  double relx2 = x2 - x1,
					  rely2 = y2 - y1,
					  topproduct = (ytop - y1) * relx2,
					  leftproduct = (xleft - x1) * rely2;
			  if(topproduct > leftproduct){
				  leftbottomregion(xleft, ytop, xright, ybottom,
				  x1, y1, x2, y2, display,
				  relx2, rely2, leftproduct);
			  }
			  else{
				  reflectxminusy(x1, y1);
				  reflectxminusy(x2, y2);
				  leftbottomregion(-ytop, -xleft, -ybottom, -xright,
				  				  x1, y1, x2, y2, display,
				  				  -rely2, -relx2, topproduct);
				  reflectxminusy(x1, y1);
				  reflectxminusy(x2, y2);
			  }
		  }
	  }
	  void NLNLineClipping::leftbottomregion(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
	  			  double &x1,double &y1,double &x2,double &y2, bool &display, const double &relx2,const double &rely2,const double &leftproduct){
		  if(y2 >= ybottom){
			  if(x2 > xright){
				  y2 = y1 + (xright - x1) * rely2/relx2;
				  x2 = xright;
			  }
			  y1 = y1 + leftproduct/relx2;
			  x1 = xleft;
			  display = true;
		  }
		  else{
			  double bottomproduct = (ybottom - y1) * relx2;
			  if(bottomproduct > leftproduct){
				  display = false;
			  }
			  else{
				  if(x2 > xright){
					  double rightproduct =  (xright - x1) * rely2;
					  if(bottomproduct > rightproduct){
						  x2 = x1 + bottomproduct/rely2;
						  y2 = ybottom;
					  }
					  else{
						  y2 = y1 + rightproduct/relx2;
						  x2 = xright;
					  }
				  }
				  else{
					  x2 = x1 + bottomproduct/rely2;
					  y2 = ybottom;
				  }
				  y1 = y1 + leftproduct/relx2;
				  x1 = xleft;
				  display = true;
			  }
		  }
	  }

	  void NLNLineClipping::leftedge(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
	  			  double &x1,double &y1,double &x2,double &y2, bool &display){
		  if(x2 < xleft) display = false;
		  else if (y2 > ytop){
			  reflectxaxis(x1, y1);	  reflectxaxis(x2, y2);
			  p2bottom(xleft, -ybottom, xright, -ytop, x1, y1, x2, y2, display);
			  reflectxaxis(x1, y1);	  reflectxaxis(x2, y2);
		  }
		  else{
			 double relx2 = x2 - x1,
					 rely2 = y2-y1;
			 if(x2 > xright){
				 y2 = y1 + rely2 * (xright - x1) / relx2;
				 x2 = xright;
			 }
			 y1 = y1 + rely2 * (xleft - x1)/relx2 ;
			 x1 = xleft;
			 display = true;
		  }
	  }

		 void NLNLineClipping::p2bottom(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
	  			  double &x1,double &y1,double &x2,double &y2, bool &display){
			double relx2 = x2 - x1,
					rely2 = y2 - y1,
					leftproduct = (xleft - x1) * rely2,
					bottomproduct = (ybottom - y1) * relx2;
			if(bottomproduct > leftproduct) display = false;
			else{
				if(x2 <= xright){
					x2 = x1 + bottomproduct/rely2;
					y2 = ybottom;
				}
				else{
					double rightproduct = (xright - x1) * rely2;
					if(bottomproduct > rightproduct){
						x2 = x1 + bottomproduct / rely2;
						y2 = ybottom;
					}
					else{
						y2 = y1 + rightproduct/relx2;
						x2 = xright;
					}
				}
				y1 = y1 + leftproduct/relx2;
				x1 = xleft;
				display = true;
			}

		}

		 void NLNLineClipping::centrecolumn(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
	  			  double &x1,double &y1,double &x2,double &y2, bool &display){
			if(y1 > ytop){
				rotate270c(x1, y1); rotate270c(x2, y2);
				leftedge (-ytop, xright, -ybottom, xleft,x1, y1, x2, y2, display);
				rotate90c(x1, y1); rotate90c (x2, y2)
			}
			else if(y1 < ybottom){
				rotate90c(x1, y1); rotate90c (x2, y2);
				leftedge (ybottom, -xleft, ytop, -xright,x1, y1, x2, y2, display);
				rotate270c(x1, y1); rotate270c(x2, y2);
			}
			else{
				inside(xleft, ytop, xright, ybottom,x1, y1, x2, y2, display);
			}
		}

		 void NLNLineClipping::inside(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
			  			  double &x1,double &y1,double &x2,double &y2, bool &display){
			 display = true;
			 if(x2 < xleft){
				 p2left(xleft, ytop, xright, ybottom,x1,y1,x2, y2);
			 }
			 else if(x2 > xright){
				 rotate180c(x1, y1); rotate180c(x2, y2);
				 p2left(-xright, -ybottom, -xleft, -ytop, x1, y1, x2, y2);
				 rotate180c(x1, y1); rotate180c (x2, y2);
			 }
			 else if(y2 > ytop){
				 x2 = x1 + (x2 -x1) * (ytop - y1)/(y2 - y1);
				 y2 = ytop;
			 }
			 else if(y2 < ybottom){
				 x2 = x1 + (x2-x1) * (ybottom-y1)/(y2-y1);
				 y2 = ybottom;
			 }
		}

		 void NLNLineClipping::p2lefttop(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
			  			  double &x1,double &y1,double &x2,double &y2){
			 double relx2 = x2 - x1,
					 rely2 = y2 - y1,
					 leftproduct = rely2 * (xleft - x1),
					 topproduct = relx2 * (ytop - y1);
			 if(topproduct > leftproduct){
				 x2 = x1 + topproduct / rely2;
				 y2 = ytop;
			 }
			 else{
				 y2 = y1 + leftproduct / relx2;
				 x2 = xleft;
			 }
		}

		 void NLNLineClipping::p2left(const double &xleft,const double &ytop,const double &xright,const double &ybottom,
	  			  double &x1,double &y1,double &x2,double &y2){
			 if(y2 > ytop){
				 p2lefttop(xleft, ytop, xright, ybottom,x1, y1, x2, y2);
			 }
			 else if (y2 < ybottom){
				 rotate90c(x1, y1); rotate90c (x2,y2);
				 p2lefttop(ybottom, -xleft, ytop, -xright,x1, y1, x2, y2);
				 rotate270c(x1, y1); rotate270c (x2,y2);
			 }
			 else{
				 y2 = y1 + (y2-y1) * (xleft-x1)/(x2-x1);
				 x2 = xleft;
			 }
		 }

}


