/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/

#include "texture.h"

Texture::Texture() {
	//Load each texture in the TEXFILES array
	for (int i = 0; i < numTex; i++) {
		if (!LoadTexture(TEXFILES[i].c_str(), i)) {
			string err = "texture " + TEXFILES[i] + " not found";
			throw err;
		}
	}
}

Texture::~Texture() {

}

bool Texture::LoadTexture(const char *imgPath, int id) {
	GLuint textureID;
	Magick::Blob blob;
	Magick::Image *image;
	//load the image
	try {
		image = new Magick::Image(imgPath);
		image->write(&blob, "RGBA");
	} catch (exception &error) {
		cerr << "Error: " << error.what() << endl;
		return false;
	}
	//generate the texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), 
				image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 
				blob.data());
	
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	delete image;

	textures[id] = textureID;
	return true;
}

GLuint Texture::GetTexture(int id) {
	return textures[id];
}