#ifndef CG_DISPLAY_FILE_H_
#define CG_DISPLAY_FILE_H_

#include <map>
#include <string>
#include "cg/GObject.h"

namespace CG {

	typedef std::map<std::string, GObject> mapGObjects;
	class DisplayFile {
		private:
			mapGObjects _objects;

		public:
			//getter
			const mapGObjects& objects() const{ return _objects;}
			mapGObjects& objects() { return _objects;}

			//add, remove and fetch objects
			GObject& add(std::string name, GObject object) {
				_objects[name] = object;
				return _objects[name];
			}
			mapGObjects::iterator findObject(const std::string& name) {return _objects.find(name);}
			bool isValidIterator(const mapGObjects::iterator it) const {return it!= _objects.end();}
  };

}

#endif
