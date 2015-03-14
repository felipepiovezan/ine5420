#ifndef CG_DISPLAY_FILE_H_
#define CG_DISPLAY_FILE_H_

#include <map>
#include <string>
#include "GObject.h"

namespace CG {

	class DisplayFile {
		private:
			typedef std::map<std::string, GObject> mapGObjects;
			mapGObjects _objects;
		
		public:
			void add(std::string name, GObject object);

			//getter
			const mapGObjects& objects() const{ return _objects;}
  };

}

#endif
