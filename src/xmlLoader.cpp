/*John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/

#include "xmlLoader.h"

XMLLoader::XMLLoader() {

}

XMLLoader::XMLLoader(const char* fileName) {
	srand(static_cast <unsigned> (time(0)));
	tinyxml2::XMLError error = configFile.LoadFile(fileName);
	if(error == tinyxml2::XML_SUCCESS) {
		throw "XML file loaded correctly!";
	} else {
		throw "error loading XML file " + string(fileName) + 
		"\nerror type: " + configFile.ErrorIDToName(error);
	}
}

XMLLoader::~XMLLoader() {

}

int XMLLoader::Init(const char* fileName) {
    srand(static_cast <unsigned> (time(0)));
	tinyxml2::XMLError error = configFile.LoadFile(fileName);
	if(error == tinyxml2::XML_SUCCESS) {
		cerr << "XML file loaded correctly!" << endl;
		return 0;
	} else {
		cerr << "error loading XML file " << fileName << endl;
		cerr << "error type: " << configFile.ErrorIDToName(error) << endl;;
		return 1;
	}
}

vector<Planet> XMLLoader::ParseXML() {
	//grab the first element
	tinyxml2::XMLElement* rootElement = configFile.RootElement()->FirstChildElement("Planet");

	while (rootElement != 0) {
		//create the next Planet struct and fill it
		const char* element;
		Planet newPlanet;

		element = rootElement->FirstChildElement("OrbitDistance")->GetText();
		newPlanet.orbitDistance = stof(element);
		
		element = rootElement->FirstChildElement("OrbitSpeed")->GetText();
		newPlanet.orbitSpeed = stof(element);

		element = rootElement->FirstChildElement("OrbitTilt")->GetText();
		newPlanet.orbitTilt = glm::radians(stof(element));	//convert degrees to radians
		
		element = rootElement->FirstChildElement("RotationSpeed")->GetText();
		newPlanet.rotateSpeed = stof(element);

		element = rootElement->FirstChildElement("ObjectIndex")->GetText();
		newPlanet.objIndex = stoi(element);

		element = rootElement->FirstChildElement("TextureIndex")->GetText();
		newPlanet.texIndex = stoi(element);

		element = rootElement->FirstChildElement("PlanetScale")->GetText();
		newPlanet.planetScale = stof(element);
		
		element = rootElement->FirstChildElement("NumMoons")->GetText();
		newPlanet.numMoons = stoi(element);

		// generate random floating point numbers for the angles
		newPlanet.orbitAngle = (float)(rand()) / ((float)(RAND_MAX / (glm::pi<float>() * 2)));
		newPlanet.rotateAngle = (float)(rand()) / ((float)(RAND_MAX / (glm::pi<float>() * 2)));

		//next loop
		planetInfo.push_back(newPlanet);
		rootElement = rootElement->NextSiblingElement("Planet");
	}

	return planetInfo;
}