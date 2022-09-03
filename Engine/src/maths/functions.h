#pragma once

#ifndef _FUNCTIONS_DEFINED
#define _FUNCTIONS_DEFINED

namespace maths {

	void quicksort(int length, int* array);

	//returns the quantity of bits given as a parameter: limit
	unsigned int partOfInt(int number, int limit);
	unsigned long partOfLong(long number, int limit);
	unsigned char partOfByte(char number, int limit);
	unsigned short partOfShort(short number, int limit);

	//finds the factorial of an integer number
	int factorial(int number);

	//finds the square root and inverse root of a number
	float sqrt(float number);
	float inv_sqrt(float number);

	double toDegree(double radian);
	double toRadians(double degree);

	float toDegree(float radian);
	float toRadians(float degree);

	float distInterpolation(float point1, float point2, float avrg);

	float interpolate(float factor, float high, float low);
}

#endif // !_FUNCTIONS_DEFINED
