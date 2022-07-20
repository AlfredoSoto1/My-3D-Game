#pragma once


#ifndef _BUFFERED_TEXTURE_DEFINED
#define _BUFFERED_TEXTURE_DEFINED

namespace texture {

	class BufferedTexture {
	public:

		BufferedTexture(unsigned int width, unsigned int height);
		~BufferedTexture();

		unsigned int getId() const;

		void bind(unsigned int slot = 0);
		void unbind();

	private:

		unsigned int width;
		unsigned int height;

		unsigned int textureId;

		unsigned int minFilter;
		unsigned int magFilter;
		unsigned int textureWrap;

		float anisotropicFilter = 0.0;

		void create();
		void anisotropicFilterLevel();
	};

}

#endif // !_BUFFERED_TEXTURE_DEFINED
