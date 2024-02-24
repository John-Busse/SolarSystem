/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/

#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "glHeaders.h"

class XMLLoader {
	public:
		XMLLoader();
		XMLLoader(const char* fileName);
		~XMLLoader();

		int Init(const char* fileName);
		vector<Planet> ParseXML();
	private:
		tinyxml2::XMLDocument configFile;
		vector<Planet> planetInfo;
};

#endif