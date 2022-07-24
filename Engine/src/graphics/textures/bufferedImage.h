#pragma once

#ifndef _BUFFERED_IMAGE_DEFINED
#define _BUFFERED_IMAGE_DEFINED


/*

	This template is to be used in the future if such code is needed

*/



namespace texture {

	class BufferedImage {
	public:

		BufferedImage(int width, int height, int channelCount, void* pixelData);
		~BufferedImage();

		void setPixelColor(int x, int y, void* color);
		void getPixelColor(int x, int y, void* color);

	private:

		unsigned int width;
		unsigned int height;

		unsigned int channelCount;

		char* pixelData;
	};

}

#endif // !_BUFFERED_IMAGE_DEFINED
