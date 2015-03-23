#include "cg/DisplayFile.h"
#include <cassert>
namespace CG {

  void DisplayFile::add(std::string name, GObject object, const Transformation& wo2wiMatrix) {
    _worldObjects[name] = object;
    object.transform(wo2wiMatrix);
    _windowObjects[name] = object;
  }

  void DisplayFile::updateWindowCoords(const Transformation &wo2wiMatrix){
	  assert(_worldObjects.size() == _windowObjects.size());

	  for(const auto &obj : _worldObjects){
		  const std::string &name = obj.first;
		  assert(_windowObjects.find(name) != _windowObjects.end());
		  _windowObjects[name] = obj.second;
		  _windowObjects[name].transform(wo2wiMatrix);
	  }
  }

}
