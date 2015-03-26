#ifndef INCLUDE_CG_OBJIO_H_
#define INCLUDE_CG_OBJIO_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "cg/GObject.h"

class ObjReader {
	public:
		ObjReader(const std::string& filename);

	private:
		typedef std::string string;

		std::ifstream ifs;
		bool good;
		std::vector<CG::Coordinate> _vertices;
		std::vector<CG::GObject> _objects;

		void init();
		void processComment(std::stringstream& line);
		void processVertex(std::stringstream& line);
		void processTexture(std::stringstream& line);
		void processNormal(std::stringstream& line);
		void processParaSpaceVertex(std::stringstream& line);
		void processFace(std::stringstream& line);
};

#endif
