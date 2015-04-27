#ifndef INCLUDE_CG_OBJIO_H_
#define INCLUDE_CG_OBJIO_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include "cg/objects.h"

class ObjReader {
	public:
		ObjReader(const std::string& filename);

		std::shared_ptr<CG::G3dObject> object() {return _object;}
	private:
		typedef std::string string;

		std::ifstream ifs;
		bool good;
		std::shared_ptr<CG::G3dObject> _object;

		void init();
		void processComment(std::stringstream& line);
		void processVertex(std::stringstream& line);
		void processTexture(std::stringstream& line);
		void processNormal(std::stringstream& line);
		void processParaSpaceVertex(std::stringstream& line);
		void processFace(std::stringstream& line);
};

class ObjWriter{
	public:
		ObjWriter(const std::string& filename);
		void writeObjects(const std::map<std::string, CG::ObjRef>& objects);

	private:
		std::ofstream ofs;
		bool good;
		int end;

		void printVertex(const CG::Coordinate& c);
		void printFace(int start, int end);
};

#endif
