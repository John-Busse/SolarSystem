/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef LIGHTING_H
#define LIGHTING_H

#include "glHeaders.h"

struct Material {
	float ambient[4], diffuse[4], specular[4], shine;
};

class Lighting {
    public:
        Lighting();
        ~Lighting();

		float* GetAmbient(int mtlIndex);
		float* GetAmbient();
		float* GetDiffuse(int mtlIndex);
		float* GetDiffuse();
		float* GetSpecular(int mtlIndex);
		float* GetSpecular();
		float GetShine(int mtlIndex);
		float GetShine();

    private:
		bool print;
		Material materials[numObj];
        const string MTLFILES[numObj] = {
			"../materials/Sun.obj", 	    //0
			"../materials/Mercury.obj",     //1
			"../materials/Venus.obj",	    //2
			"../materials/Earth.obj",	    //3
			"../materials/Mars.obj",	    //4
			"../materials/Jupiter.obj",	    //5
			"../materials/Saturn.obj",	    //6
			"../materials/Uranus.obj",	    //7
			"../materials/Neptune.obj",	    //8
			"../materials/Pluto.obj",	    //9
			"../materials/Moon.obj",	    //10
			"../materials/BigRing.obj",	    //11
			"../materials/SmallRing.obj"};	//12
};

#endif