#include "bufferedTexture.h"

#include <GL/glew.h>
#include "../../exceptions/Error.h"
#include <iostream>
#include <stdlib.h>

using namespace texture;

BufferedTexture::BufferedTexture(unsigned int width, unsigned int height, void* pixels) : 
width(width), height(height), pixels(pixels) {
	glGenTextures(1, &textureId);

	create();
}

BufferedTexture::~BufferedTexture() {
	glDeleteTextures(1, &textureId);
}

unsigned int BufferedTexture::getId() const {
	return textureId;
}

void BufferedTexture::create() {

	minFilter = GL_NEAREST;// GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR;
	magFilter = GL_NEAREST;// GL_LINEAR;

	textureWrap = GL_CLAMP_TO_EDGE;// GL_REPEAT; //GL_CLAMP_TO_EDGE;
	
	error::glClearError();

	glBindTexture(GL_TEXTURE_2D, textureId);//bind

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	if (minFilter == GL_NEAREST_MIPMAP_NEAREST || minFilter == GL_LINEAR_MIPMAP_LINEAR) {
		glGenerateMipmap(GL_TEXTURE_2D);
		if (anisotropicFilter != 0.0f) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0);
		}
		anisotropicFilterLevel();
	}

	if (textureWrap == GL_CLAMP_TO_BORDER) {
		float param[4] = {0.0, 0.0, 0.0, 1.0};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, param);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);

	//simple image
	char* pixels = new char[width * height * 4];
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			pixels[(x + y * width) * 4 + 0] = rand() % 255;
			pixels[(x + y * width) * 4 + 1] = rand() % 255;
			pixels[(x + y * width) * 4 + 2] = rand() % 255;
			pixels[(x + y * width) * 4 + 3] = 255;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pixels);

	delete[] pixels;

	glBindTexture(GL_TEXTURE_2D, 0);//unbind

	error::glCheckError();
}

void BufferedTexture::anisotropicFilterLevel() {
	if (GL_EXT_texture_filter_anisotropic == GL_TRUE) {
		float anisotropy = anisotropicFilter;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
		anisotropy = (anisotropicFilter > anisotropy) ? anisotropy : anisotropicFilter;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
	}
	else {
		std::cout << "Anisotropic Filtering not Compatible." << std::endl;
	}
}

void BufferedTexture::setWrap(unsigned int wrap) {

}

void BufferedTexture::setFilter(unsigned int filter) {

}

void BufferedTexture::setMipmapLevel(float mipmapLevel) {

}

void BufferedTexture::setAnisotropicFilter(float anisotropicFilter) {

}

void BufferedTexture::setPixels(void* pixels) {

}

void BufferedTexture::bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void BufferedTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

//image class

void getPixels(int x, int y, int width, int channels, char* pixels) {
	pixels[(x + y * width) * channels + 0] = 255;
	pixels[(x + y * width) * channels + 1] = 0;
	pixels[(x + y * width) * channels + 2] = 255;
	pixels[(x + y * width) * channels + 3] = 255;
}