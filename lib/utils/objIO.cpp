#include "utils/objIO.h"
#include <iostream>

ObjReader::ObjReader(const std::string &filename) : ifs(filename), good(true), _object(new CG::G3dObject()) {
	if(!ifs){
		good = false;
		std::cerr << "Failed to open file " << filename << std::endl;
		return;
	}
	init();
}

int linenum = 0;
void ObjReader::init(){
	string lineString, opCode;
	while(std::getline(ifs, lineString)){
		if(lineString.size() <= 1) continue;
		linenum++;
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
	if(!line){ std::cerr << "Invalid vertex format @line = " << linenum << " "<< line.str() << std::endl; return;}
	if(!(line >> w))
		w = 1.0;
	_object->coordinates().push_back(CG::Coordinate(x,y,z));
}

void ObjReader::processTexture(std::stringstream& line){

}

void ObjReader::processNormal(std::stringstream& line){

}

void ObjReader::processParaSpaceVertex(std::stringstream& line){

}

void ObjReader::processFace(std::stringstream& line){
	string pointString;
	int vertexIndex, textureIndex = -1, normalIndex = -1;
	std::vector<int> face;

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

		if(vertexIndex > 0 && vertexIndex > _object->coordinates().size()){
			std::cerr << "Vertex index (" << vertexIndex << ") out of bounds @line = " << line.str() << std::endl;
			return;
		}
		else if (vertexIndex > 0 ){
			face.push_back(vertexIndex - 1);
		}
		//relative indexing
		if(vertexIndex < 0 && _object->coordinates().size() + vertexIndex >= 0){
			face.push_back(_object->coordinates().size() + vertexIndex);
		}
	}
	_object->faceList().push_back(std::move(face));
}

ObjWriter::ObjWriter (const std::string &filename) : ofs(filename), good(true), end(1) {
	if(!ofs){
		good = false;
		std::cerr << "Failed to open file " << filename << std::endl;
		return;
	}
}

void ObjWriter::writeObjects(const std::map<std::string, CG::ObjRef>& objects){
	if(!good){
		std::cerr << "Object writer was not successfully opened" << std::endl;
		return;
	}
	for(const auto &obj : objects){
		assert(obj.second->numPoints() > 0);
		int start = end;
		for(const auto &coord : obj.second->coordinates())
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
