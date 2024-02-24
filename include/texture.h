/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include "glHeaders.h"

class Texture {
	public:
		Texture();
		~Texture();

		bool LoadTexture(const char *imgPath, int id);
		GLuint GetTexture(int id);

	private:
		const string TEXFILES[numObj] = {
			"../textures/Sun.jpg", 			//0
			"../textures/Mercury.jpg", 		//1
			"../textures/Venus.jpg",		//2
			"../textures/Earth.jpg",		//3
			"../textures/Mars.jpg",			//4
			"../textures/Jupiter.jpg",		//5
			"../textures/Saturn.jpg",		//6
			"../textures/Uranus.jpg",		//7
			"../textures/Neptune.jpg",		//8
			"../textures/Pluto.jpg",		//9
			"../textures/Moon.jpg",			//10
			"../textures/BigRing.jpg",		//11
			"../textures/SmallRing.jpg"};	//12
		GLuint textures[numObj];
};

#endif