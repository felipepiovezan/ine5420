#include "Transformations.h"

namespace CG{

	Transformation Transformation::newTranslation(float dx, float dy){
		return Transformation
			({{ {1,  0,  0},
				{0,  1,  0},
				{dx, dy, 1}}});
	}
	
	Transformation Transformation::newScaling(float sx, float sy){
		return Transformation
			({{ {sx, 0 , 0},
				{0 , sy, 0},
				{0 , 0 , 1}}});
	}
	
	Transformation Transformation::newRotation(float theta){
		return Transformation
			({{ {cos(theta), -sin(theta), 0},
				{sin(theta), cos(theta) , 0},
				{0         , 0          , 1}}});
	}

	Transformation operator+(const Transformation& lhs, const Transformation& rhs){
//		const auto &m1 = lhs.m();
//		const auto &m2 = rhs.m();
		return Transformation::newScaling(1,1);
	}

}
