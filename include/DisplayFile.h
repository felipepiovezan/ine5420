#ifndef CG_DISPLAY_FILE_H_
#define CG_DISPLAY_FILE_H_

#include <map>
#include <string>
#include "GObject.h"

namespace CG {

	typedef std::map<std::string, GObject> mapGObjects;
	class DisplayFile {
		private:
			mapGObjects _objects;

		public:
			void add(std::string name, GObject object);

			//getter
			const mapGObjects& objects() const{ return _objects;}
			mapGObjects::iterator findObject(const std::string& name) {return _objects.find(name);}
			bool isValidIterator(const mapGObjects::iterator it) const {return it!= _objects.end();}

  };

}

#endif
