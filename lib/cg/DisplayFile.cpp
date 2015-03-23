#include "cg/DisplayFile.h"

namespace CG {

  void DisplayFile::add(std::string name, GObject object, const Transformation& wo2wiMatrix) {
    _worldObjects[name] = object;
    object.transform(wo2wiMatrix);
    _windowObjects[name] = object;
  }

}
