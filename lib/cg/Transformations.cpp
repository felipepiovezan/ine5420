#include "cg/Transformations.h"

namespace CG {

	Transformation::Transformation(){
		_m[0][0] = _m[1][1] = _m[2][2] = 1;
	}

	Transformation& Transformation::operator*=(const Transformation& rhs){
		auto m1 = this->_m;
		const auto &m2 = rhs.m();
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++){
				_m[i][j]=0;
				for(int k=0; k<3; k++)
					_m[i][j] += m1[i][k] * m2[k][j];
			}

		return *this;
	}

	Transformation operator*(Transformation lhs, const Transformation& rhs){
		lhs *= rhs;
		return lhs;
	}
	
	Transformation Transformation::newTranslation(double dx, double dy){
		return Transformation
			({{ {1,  0,  0},
				{0,  1,  0},
				{dx, dy, 1}}});
	}

	Transformation Transformation::newScaling(double sx, double sy){
		return Transformation
			({{ {sx, 0 , 0},
				{0 , sy, 0},
				{0 , 0 , 1}}});
	}

	Transformation Transformation::newRotationAroundOrigin(double theta){
		return Transformation
			({{ {cos(theta), -sin(theta), 0},
				{sin(theta), cos(theta) , 0},
				{0         , 0          , 1}}});
	}

	Transformation Transformation::newRotationAroundPoint(double theta, const Coordinate &p){
		return newTranslation(-p.x, -p.y) * newRotationAroundOrigin(theta) * newTranslation(p.x, p.y);
	}

	Transformation Transformation::newRotationAroundCenterOfMass(double theta, const GObject& obj){
		const Coordinate center = obj.center();
		return newRotationAroundPoint(theta, center);
	}

}
