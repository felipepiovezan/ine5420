#include "cg/Transformations.h"

namespace CG {

	std::ostream& operator<<(std::ostream& os, const Transformation& rhs){
		  for(int i=0; i<4; i++){
			  for(int j=0; j<4; j++)
				  os << os.width(8) << rhs.m()[i][j] << " ";
			  os << std::endl;
		  }
		  return os;
	 }

	Transformation::Transformation(){
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				_m[i][j] = 0;
		_m[0][0] = _m[1][1] = _m[2][2] = _m[3][3] = 1;
	}

	Transformation& Transformation::operator*=(const Transformation& rhs){
		auto m1 = this->_m;
		const auto &m2 = rhs.m();
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++){
				_m[i][j]=0;
				for(int k=0; k<4; k++)
					_m[i][j] += m1[i][k] * m2[k][j];
			}

		return *this;
	}

	Transformation Transformation::transpose(){
		TransformationMatrix mat;
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				mat[i][j] = _m[j][i];
		return Transformation(std::move(mat));

	}

	Transformation operator*(Transformation lhs, const Transformation& rhs){
		lhs *= rhs;
		return lhs;
	}

	Transformation Transformation::newTranslation(double dx, double dy, double dz){
		return Transformation
			({{ {1,  0,  0,  0},
				{0,  1,  0,  0},
				{0,  0,  1,  0},
				{dx, dy, dz, 1}}});
	}

	Transformation Transformation::newScaling(double sx, double sy, double sz){
		return Transformation
			({{ {sx, 0 , 0 , 0},
				{0 , sy, 0 , 0},
				{0 , 0 , sz, 0},
				{0 , 0 , 0 , 1}}});
	}

	Transformation Transformation::newRx(double theta){
		return Transformation
				({{ {1, 0         , 0          , 0},
					{0, cos(theta), sin(theta), 0},
					{0, -sin(theta), cos(theta) , 0},
					{0, 0         , 0          , 1}}});
	}

	Transformation Transformation::newRy(double theta){
			return Transformation
				({{ {cos(theta) , 0, -sin(theta), 0},
					{0          , 1, 0         , 0},
					{sin(theta), 0, cos(theta), 0},
					{0          , 0, 0         , 1}}});
	}

	Transformation Transformation::newRz(double theta){
			return Transformation
				({{ {cos(theta), sin(theta), 0, 0},
					{-sin(theta), cos(theta) , 0, 0},
					{0         , 0          , 1, 0},
					{0         , 0          , 0, 1}}});
	}

	Transformation Transformation::newScalingAroundObjCenter(double sx, double sy, double sz, const Coordinate& center){
		return newTranslation(-center.x, -center.y, -center.z) * newScaling(sx, sy, sz) * newTranslation(center.x, center.y, center.z);
	}

	Transformation Transformation::newRotation(double thetaX, double thetaY, double thetaZ, const Coordinate& p) {
		return  newTranslation(-p.x, -p.y, -p.z) *
						newRx(thetaX) *
						newRy(thetaY) *
						newRz(thetaZ) *
						newTranslation(p.x, p.y, p.z);
	}

}
