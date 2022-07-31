#pragma once


#ifndef _BUFFERED_TEXTURE_DEFINED
#define _BUFFERED_TEXTURE_DEFINED

namespace texture {

	class BufferedTexture {
	public:

		BufferedTexture(unsigned int width, unsigned int height, void* pixels);
		BufferedTexture(unsigned int width, unsigned int height, int slot, void* pixels);
		~BufferedTexture();

		unsigned int getId() const;
		unsigned int getFormat() const;
		int getInternalFormat() const;

		void setWrap(unsigned int wrap);
		void setFilter(unsigned int filter);
		void setMipmapLevel(float mipmapLevel = 0.0f);
		void setAnisotropicFilter(float anisotropicFilter = 0.0f);

		void setPixelData(void* pixels);
		void getPixelData(void* pixels);

		void bind(int slot = 0);
		void unbind();

	private:

		unsigned int width;
		unsigned int height;

		unsigned int textureId;

		unsigned int minFilter;
		unsigned int magFilter;
		unsigned int textureWrap;

		int internalFormat;
		unsigned int format;

		unsigned int type;

		int slot = -1;

		float mipmapLevel = 0.0f;
		float anisotropicFilter = 0.0f;

		void initializeVariables();
		void setTextureParameters();
		void anisotropicFilterLevel();
	};

}

#endif // !_BUFFERED_TEXTURE_DEFINED
