#ifndef CG_DISPLAY_FILE_H_
#define CG_DISPLAY_FILE_H_

#include <map>
#include <string>
#include "cg/GObject.h"

namespace CG {

	typedef std::map<std::string, GObject> mapGObjects;
	class DisplayFile {
		private:
			mapGObjects _worldObjects;
			mapGObjects _windowObjects;

		public:
			//getter
			const mapGObjects& windowObjects() const{ return _windowObjects;}

			//add, remove and fetch objects
			void add(std::string name, GObject object, const Transformation& wo2wiMatrix);
			mapGObjects::iterator findWorldObject(const std::string& name) {return _worldObjects.find(name);}
			mapGObjects::iterator findWindowObject(const std::string& name) {return _windowObjects.find(name);}
			bool isValidWorldIterator(const mapGObjects::iterator it) const {return it!= _worldObjects.end();}
			bool isValidWindowIterator(const mapGObjects::iterator it) const {return it!= _windowObjects.end();}
			mapGObjects::size_type removeObject(const std::string& name) {_worldObjects.erase(name); return _windowObjects.erase(name);}
  };

}

#endif
