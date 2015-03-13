#ifndef CG_DISPLAY_FILE_H_
#define CG_DISPLAY_FILE_H_

#include <map>
#include <string>
#include "GObject.h"

namespace CG {

  class DisplayFile {
  public:
    void add(std::string name, GObject *object);

    typedef std::map<std::string, GObject *>::iterator Iterator;

    Iterator begin() {
      return objects.begin();
    }

    Iterator end() {
      return objects.end();
    }

  protected:
    std::map<std::string, GObject *> objects;
  };

}

#endif
