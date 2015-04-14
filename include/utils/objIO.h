#ifndef INCLUDE_CG_OBJIO_H_
#define INCLUDE_CG_OBJIO_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "cg/GObject.h"
#include <cassert>
#include <memory>

class ObjReader {
	public:
		ObjReader(const std::string& filename);

		const std::vector<std::shared_ptr<CG::GObject>>& objects() {return _objects;}
	private:
		typedef std::string string;

		std::ifstream ifs;
		bool good;
		std::vector<CG::Coordinate> _vertices;
		std::vector<std::shared_ptr<CG::GObject>> _objects;

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
		void writeObjects(const std::map<std::string, std::shared_ptr<CG::GObject>>& objects);

	private:
		std::ofstream ofs;
		bool good;
		int end;

		void printVertex(const CG::Coordinate& c);
		void printFace(int start, int end);
};

#endif
