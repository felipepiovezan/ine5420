#include "cg/ClippingStrategy.h"

namespace CG{
  	  #define rotate90c(x,y) {double __t=x; x=y; y=-__t;}
  	  #define rotate180c(x,y) x=-x; y=-y;
  	  #define rotate270(x,y) {double __t=x; x=-y; y=__t;}
  	  #define reflectxminusy(x,y) {double __t=x; x=-y; y=-__t;}
  	  #define reflectxaxis(x,y) y=-y;

	  bool NLNLineClipping::clipLine(GLine& l, ClippingRect& rect){
		  const double &xleft = rect.minX,
				  &xright = rect.maxX,
				  &ybottom = rect.minY,
				  &ytop = rect.maxY;
		  double &x1 = l.coordinates()[0].x,
				  &y1 = l.coordinates()[0].y,
				  &x2 = l.coordinates()[1].x,
				  &y2 = l.coordinates()[1].y;
		  bool display=false;
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
		  if(y2 < ytop) display = false;
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
				  				  -relx2, -rely2, topproduct);
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

  }
