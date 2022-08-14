#include "functions.h"
#include "constants.h"

using namespace maths;

void swap(int* array, int index1, int index2) {
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

void quicksortByIndex(int* array, int lowIndex, int highIndex) {

	if (lowIndex >= highIndex)
		return;

	int pivot = array[highIndex];
	int leftPointer = lowIndex;
	int rightPointer = highIndex;

	while (leftPointer < rightPointer) {
		while (array[leftPointer] <= pivot && leftPointer < rightPointer) {
			leftPointer++;
		}

		while (array[rightPointer] >= pivot && leftPointer < rightPointer) {
			rightPointer--;
		}
		swap(array, leftPointer, rightPointer);
	}
	if (array[leftPointer] > array[highIndex]) {
		swap(array, leftPointer, highIndex);
	}
	else {
		leftPointer = highIndex;
	}

	quicksortByIndex(array, lowIndex, leftPointer - 1);
	quicksortByIndex(array, leftPointer + 1, highIndex);
}

void maths::quicksort(int length, int* array) {
	quicksortByIndex(array, 0, length - 1);
}

unsigned long maths::partOfLong(long number, int limit) {
	int shift_Ammount = 64 - limit;
	return ((unsigned long)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned int maths::partOfInt(int number, int limit) {
	int shift_Ammount = 32 - limit;
	return ((unsigned int)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned short maths::partOfShort(short number, int limit) {
	int shift_Ammount = 16 - limit;
	return ((unsigned short)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned char maths::partOfByte(char number, int limit) {
	int shift_Ammount = 8 - limit;
	return ((unsigned char)(number << shift_Ammount)) >> shift_Ammount;
}


int maths::factorial(int number) {
	int result = 1;
	for (int i = 1; i <= number; i++)
		result *= i;
	return result;
}

float maths::sqrt(float number) {
	return inv_sqrt(number) * number;
}

float maths::inv_sqrt(float number) {
	int i;
	float x2, y;

	x2 = number * 0.5f;
	y = number;
	i = *(int*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5F - (x2 * y * y));
	//y = y * (1.5F - (x2 * y * y));
	return y;
}

double maths::toDegree(double radian) {
	return (180.0 / PI) * radian;
}

double maths::toRadians(double degree) {
	return (PI / 180.0) * degree;
}

float maths::toDegree(float radian) {
	return (180.0f / PI) * radian;
}

float maths::toRadians(float degree) {
	return (PI / 180.0f) * degree;
}

float maths::distInterpolation(float value1, float value2, float avrg) {
	return value1 + (value2 - value1) * avrg;
}

float maths::interpolate(float factor, float high, float low) {
	return (factor - low) / (high - low);
}