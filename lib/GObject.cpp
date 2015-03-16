#include "GObject.h"

namespace CG {
	void Coordinate::applyTransformation(const Transformation& t){
		const float (&m)[3][3] = t.m;
		float x = this->x, y = this->y, z = this->z;
		this->x = x*m[0][0] + y*m[1][0] + z*m[2][0];
		this->y = x*m[0][1] + y*m[1][1] + z*m[2][1];
		this->z = x*m[0][2] + y*m[1][2] + z*m[2][2];
	}

	void GObject::applyTransformation(const Transformation& t){
		for(auto &p : _coordinates){
			p.applyTransformation(t);
		}
	}
}
