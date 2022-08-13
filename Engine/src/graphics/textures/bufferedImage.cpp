#include "bufferedImage.h"

using namespace texture;

BufferedImage::BufferedImage(int width, int height, int channelCount, void* pixelData) :
	width(width), height(height), channelCount(channelCount) 
{
	if (channelCount > 4)
		channelCount = 4;
	else if (channelCount < 1)
		channelCount = 1;

	this->pixelData = new char[width * height * channelCount];

}

BufferedImage::~BufferedImage() {
	delete[] this->pixelData;
}

void BufferedImage::setPixelColor(int x, int y, void* color) {
	for (int i = 0; i < channelCount; i++)
		pixelData[(x + y * width) * 4 + i] = 0;
}

void BufferedImage::getPixelColor(int x, int y, void* color) {
	for (int i = 0; i < channelCount; i++)
		pixelData[(x + y * width) * 4 + i] = 0;
}