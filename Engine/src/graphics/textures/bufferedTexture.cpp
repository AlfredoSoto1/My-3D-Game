#include "bufferedTexture.h"

#include <GL/glew.h>
#include <iostream>

#include "../../exceptions/Error.h"

using namespace texture;

BufferedTexture::BufferedTexture(unsigned int width, unsigned int height, void* pixels) : 
width(width), height(height) {
	glGenTextures(1, &textureId);

	initializeVariables();

	error::glClearError();
	glBindTexture(GL_TEXTURE_2D, textureId);
	setTextureParameters();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, (void*)pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	error::glCheckError();
}

BufferedTexture::BufferedTexture(unsigned int width, unsigned int height, int slot, void* pixels) :
	width(width), height(height), slot(slot) {
	glGenTextures(1, &textureId);

	initializeVariables();

	error::glClearError();
	glBindTexture(GL_TEXTURE_2D, textureId);
	setTextureParameters();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, (void*)pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	error::glCheckError();
}

BufferedTexture::~BufferedTexture() {
	glDeleteTextures(1, &textureId);
}

unsigned int BufferedTexture::getId() const {
	return textureId;
}

unsigned int BufferedTexture::getFormat() const {
	return format;
}

int BufferedTexture::getInternalFormat() const {
	return internalFormat;
}

void BufferedTexture::setWrap(unsigned int wrap) {
	this->textureWrap = wrap;
}

void BufferedTexture::setFilter(unsigned int filter) {
	this->minFilter = filter;
	this->magFilter = filter;
}

void BufferedTexture::setMipmapLevel(float mipmapLevel) {
	this->mipmapLevel = mipmapLevel;
}

void BufferedTexture::setAnisotropicFilter(float anisotropicFilter) {
	this->anisotropicFilter = anisotropicFilter;
}

void BufferedTexture::initializeVariables() {
	minFilter = GL_NEAREST;// GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR;
	magFilter = GL_NEAREST;// GL_LINEAR;

	textureWrap = GL_REPEAT;// GL_REPEAT; //GL_CLAMP_TO_EDGE;

	format = GL_RGBA;
	internalFormat = GL_RGBA8;

	type = GL_UNSIGNED_BYTE;
}

void BufferedTexture::setTextureParameters() {
	//set filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	//set mip-mapping and anisotropic filtering
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

	//texture border (optional)
	if (textureWrap == GL_CLAMP_TO_BORDER) {
		float param[4] = { 0.0, 0.0, 0.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, param);
	}

	//texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
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

void BufferedTexture::setPixelData(void* pixels) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BufferedTexture::getPixelData(void* pixels) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, format, type, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BufferedTexture::bind(int slot) {
	if(this->slot < 0)
		glActiveTexture(GL_TEXTURE0 + slot);
	else
		glActiveTexture(GL_TEXTURE0 + this->slot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void BufferedTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

//image class
//
//void tempFunc(int x, int y, int width, int channels, char* pixels) {
//	pixels[(x + y * width) * channels + 0] = 255;
//	pixels[(x + y * width) * channels + 1] = 0;
//	pixels[(x + y * width) * channels + 2] = 255;
//	pixels[(x + y * width) * channels + 3] = 255;
//
//	//simple image
//	char* pixels = new char[width * height * 4];
//	for (int x = 0; x < width; x++) {
//		for (int y = 0; y < height; y++) {
//			pixels[(x + y * width) * 4 + 0] = rand() % 255;
//			pixels[(x + y * width) * 4 + 1] = rand() % 255;
//			pixels[(x + y * width) * 4 + 2] = rand() % 255;
//			pixels[(x + y * width) * 4 + 3] = 255;
//		}
//	}
//}