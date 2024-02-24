/* John Busse jbusse@nevada.unr.edu
clearComputer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef HEADERS_H
#define HEADERS_H

//standard c++ libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>

//opengl libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//glm libraries (openGL mathematics)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

//assimp libraries
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//magick++
#include <Magick++.h>

//xml parsing library
#include "tinyxml2.h"

using namespace std;

#define numVAOs 1
#define numVBOs 3	//number of vertex buffer objects (3D models used)
#define numObj 13	//number of objects

struct Vertex {
	glm::vec3 vertex;
	glm::vec2 texture;

	//Vertex(glm::vec3 v): vertex(v) {}
	Vertex(glm::vec3 v, glm::vec2 t): vertex(v), texture(t) {}
};

struct Planet {
	string planetName;
	int numMoons;
	float planetScale;
	unsigned short int objIndex, texIndex, plaIndex;
	// orbit info
	float orbitDistance, orbitSpeed, orbitTilt, orbitAngle;
	// rotation info
	float rotateSpeed, rotateAngle;
	//glm::vec3 rotAxis;
};

#endif