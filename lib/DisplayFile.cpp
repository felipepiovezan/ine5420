#include "DisplayFile.h"

namespace CG {

  void DisplayFile::add(std::string name, GObject object) {
    _objects[name] = object;
  }

}
