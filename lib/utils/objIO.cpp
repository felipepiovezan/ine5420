#include "utils/objIO.h"
#include <iostream>

ObjReader::ObjReader(const std::string &filename) : ifs(filename), good(true) {
	if(!ifs){
		good = false;
		std::cerr << "Failed to open file " << filename << std::endl;
		return;
	}
	init();
}

void ObjReader::init(){
	string lineString, opCode;
	while(std::getline(ifs, lineString)){
		std::stringstream line(lineString);
		line >> opCode;
		if(opCode == "#")	{ processComment(line); 		continue;}
		if(opCode == "v")	{ processVertex(line); 			continue;}
		if(opCode == "vt")	{ processTexture(line);			continue;}
		if(opCode == "vn")	{ processNormal(line);			continue;}
		if(opCode == "vp")	{ processParaSpaceVertex(line);	continue;}
		if(opCode == "f")	{ processFace(line);			continue;}
		std::cerr << "Invalid opcode @line = " << line.str() << std::endl;
	}
}

void ObjReader::processComment(std::stringstream& line){

}

void ObjReader::processVertex(std::stringstream& line){
	double x,y,z,w;
	line >> x >> y >> z;
	if(!line){ std::cerr << "Invalid vertex format @line = " << line.str() << std::endl; return;}
	if(!(line >> w))
		w = 1.0;
	_vertices.push_back(CG::Coordinate(x,y));
}

void ObjReader::processTexture(std::stringstream& line){

}

void ObjReader::processNormal(std::stringstream& line){

}

void ObjReader::processParaSpaceVertex(std::stringstream& line){

}

void ObjReader::processFace(std::stringstream& line){
	std::cout<<line.str() << std::endl;
	string pointString;
	unsigned int vertexIndex, textureIndex = -1, normalIndex = -1;
	std::vector<CG::Coordinate> coords;

	while(line >> pointString){
		//First index (vertex) is mandatory
		std::stringstream point(pointString);
		point >> vertexIndex;
		if(!point){ std::cerr << "Invalid face format @line = " << line.str() << std::endl; return;}

		//Are there more indices to read? (texture and/or normal)
		if(point.peek() == '/'){
			point.ignore(1);

			//Only normal index left;
			if(point.peek() == '/'){
				point.ignore(1);
				point >> normalIndex;
				if(!point){ std::cerr << "Invalid face format @line = " << line.str() << std::endl; return;}
			}
			//Texture index is present
			else{
				point >> textureIndex;
				if(!point){ std::cerr << "Invalid face format @line = " << line.str() << std::endl; return;}

				//Normal index present?
				if(point.peek() == '/'){
					point.ignore(1);
					point >> normalIndex;
					if(!point){ std::cerr << "Invalid face format @line = " << line.str() << std::endl; return;}
				}
			}
		}

		if(vertexIndex > _vertices.size()) { std::cerr << "Vertex index (" << vertexIndex << ") out of bounds @line = " << line.str() << std::endl; return;}
		coords.push_back(_vertices[vertexIndex-1]);
		std::cout << "\tvertex, texture, normal = " << vertexIndex << ", " << textureIndex << ", " << normalIndex << std::endl;
	}

	//TODO: this is ugly. We need an universal constructor for GObjects which receives a vector<Coords>.
	// this can't be done right now thanks to the way the "object type" is instanciated.
	if(coords.size() == 1)
		_objects.push_back(CG::GPoint(coords[0]));
	else if (coords.size() == 2)
		_objects.push_back(CG::GLine(coords[0], coords[1]));
	else if (coords.size() > 2)
		_objects.push_back(CG::GPolygon(coords));
}

ObjWriter::ObjWriter (const std::string &filename) : ofs(filename), good(true), end(1) {
	if(!ofs){
		good = false;
		std::cerr << "Failed to open file " << filename << std::endl;
		return;
	}
}

void ObjWriter::writeObjects(const std::map<std::string, CG::GObject>& objects){
	if(!good){
		std::cerr << "Object writer was not successfully opened" << std::endl;
		return;
	}
	for(const auto &obj : objects){
		assert(obj.second.numPoints() > 0);
		int start = end;
		for(const auto &coord : obj.second.coordinates())
			printVertex(coord);
		printFace(start, end);
	}
}

void ObjWriter::printVertex(const CG::Coordinate& c){
	ofs << "v " << c.x << " " << c.y << " " << 1.0 << " " << c.w << std::endl;
	end++;
}

void ObjWriter::printFace(int start, int end){
	if(start == end) return;

	ofs << "f";
	for(int i=start; i < end; i++)
		ofs << " " << i;
	ofs << std::endl;
}
