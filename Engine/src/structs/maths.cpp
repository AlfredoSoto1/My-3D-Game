#include "maths.h"

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

void algoritm::quicksort(int length, int* array) {
	quicksortByIndex(array, 0, length - 1);
}

unsigned long algoritm::partOfLong(long number, int limit) {
	int shift_Ammount = 64 - limit;
	return ((unsigned long)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned int algoritm::partOfInt(int number, int limit) {
	int shift_Ammount = 32 - limit;
	return ((unsigned int)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned short algoritm::partOfShort(short number, int limit) {
	int shift_Ammount = 16 - limit;
	return ((unsigned short)(number << shift_Ammount)) >> shift_Ammount;
}

unsigned char algoritm::partOfByte(char number, int limit) {
	int shift_Ammount = 8 - limit;
	return ((unsigned char)(number << shift_Ammount)) >> shift_Ammount;
}


int functions::factorial(int number) {
	int result = 1;
	for (int i = 1; i <= number; i++)
		result *= i;
	return result;
}

float functions::sqrt(float number) {
	return inv_sqrt(number) * number;
}

float functions::inv_sqrt(float number) {
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

/*
	Vector 2f Implementation
*/

using namespace structs;

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float xy) : x(xy), y(xy) {}
vec2::vec2(float x, float y) : x(x), y(y) {}
vec2::vec2(const vec2& vector) : x(vector.x), y(vector.y) {}

void vec2::set(float x, float y) {
	this->x = x;
	this->y = y;
}

float& vec2::operator [] (unsigned int index) {
	return *((float*)this + (1 & index));
}

vec2 vec2::operator + (const vec2& vector) {
	return vec2(x + vector.x, y + vector.y);
}

vec2 vec2::operator - (const vec2& vector) {
	return vec2(x - vector.x, y - vector.y);
}

vec2 vec2::operator * (const float factor) {
	return vec2(x * factor, y * factor);
}

vec2 vec2::operator / (const float factor) {
	return vec2(x / factor, y / factor);
}

float vec2::operator * (const vec2& vector) {
	return dot(*this, vector);
}

vec2& vec2::operator += (const vec2& vector) {
	x = x + vector.x;
	y = y + vector.y;
	return *this;
}

vec2& vec2::operator -= (const vec2& vector) {
	x = x - vector.x;
	y = y - vector.y;
	return *this;
}

vec2& vec2::operator *= (const float factor) {
	for (int i = 0; i < 2; i++)
		(*this)[i] *= factor;
	return *this;
}

vec2& vec2::operator /= (const float factor) {
	for (int i = 0; i < 2; i++)
		(*this)[i] /= factor;
	return *this;
}

bool vec2::operator == (const float value) {
	return value == x && value == y;
}

bool vec2::operator == (const vec2& vector) {
	return vector.x == x && vector.y == y;
}

bool vec2::operator != (const vec2& vector) {
	return !(*this == vector);
}

/*

	Vector 3f Implementation

*/

vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
vec3::vec3(float xyz) : x(xyz), y(xyz), z(xyz) {}
vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}
vec3::vec3(const vec3& vector) : x(vector.x), y(vector.y), z(vector.z) {}
vec3::vec3(const vec2& vector, float z) : x(vector.x), y(vector.y), z(z) {}

void vec3::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float& vec3::operator [] (unsigned int index) {
	return *((float*)this + (2 & index));
}

vec3 vec3::operator + (const vec3& vector) {
	return vec3(x + vector.x, y + vector.y, z + vector.z);
}

vec3 vec3::operator - (const vec3& vector) {
	return vec3(x - vector.x, y - vector.y, z - vector.z);
}

vec3 vec3::operator * (const float factor) {
	return vec3(x * factor, y * factor, z * factor);
}

vec3 vec3::operator / (const float factor) {
	return vec3(x / factor, y / factor, z / factor);
}

float vec3::operator * (const vec3& vector) {
	return dot(*this, vector);
}

vec3& vec3::operator += (const vec3& vector) {
	x = x + vector.x;
	y = y + vector.y;
	z = z + vector.z;
	return *this;
}

vec3& vec3::operator -= (const vec3& vector) {
	x = x - vector.x;
	y = y - vector.y;
	z = z - vector.z;
	return *this;
}

vec3& vec3::operator *= (const float factor) {
	for (int i = 0; i < 3; i++)
		(*this)[i] *= factor;
	return *this;
}

vec3& vec3::operator /= (const float factor) {
	for (int i = 0; i < 3; i++)
		(*this)[i] /= factor;
	return *this;
}

vec3 vec3::operator | (const vec3& vector) {
	return cross(*this, vector);
}

bool vec3::operator == (const float value) {
	return value == x && value == y && value == z;
}

bool vec3::operator == (const vec3& vector) {
	return vector.x == x && vector.y == y && vector.z == z;
}

bool vec3::operator != (const vec3& vector) {
	return !(*this == vector);
}

/*

	Vector 4f Implementation

*/

vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
vec4::vec4(const vec4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}
vec4::vec4(const vec3& vector, float w) : x(vector.x), y(vector.y), z(vector.z), w(w) {}
vec4::vec4(const vec2& vector, float z, float w) : x(vector.x), y(vector.y), z(z), w(w) {}
vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
vec4::vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

void vec4::set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float& vec4::operator [] (unsigned int index) {
	return *((float*)this + (3 & index));
}

vec4 vec4::operator + (const vec4& vector) {
	return vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

vec4 vec4::operator - (const vec4& vector) {
	return vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

vec4 vec4::operator * (const float factor) {
	return vec4(x * factor, y * factor, z * factor, w * factor);
}

vec4 vec4::operator / (const float factor) {
	return vec4(x / factor, y / factor, z / factor, w / factor);
}

float vec4::operator * (const vec4& vector) {
	return dot(*this, vector);
}

vec4& vec4::operator += (const vec4& vector) {
	x = x + vector.x;
	y = y + vector.y;
	z = z + vector.z;
	w = w + vector.w;
	return *this;
}
vec4& vec4::operator -= (const vec4& vector) {
	x = x - vector.x;
	y = y - vector.y;
	z = z - vector.z;
	w = w - vector.w;
	return *this;
}
vec4& vec4::operator *= (const float factor) {
	for (int i = 0; i < 4; i++)
		(*this)[i] *= factor;
	return *this;
}
vec4& vec4::operator /= (const float factor) {
	for (int i = 0; i < 4; i++)
		(*this)[i] /= factor;
	return *this;
}

bool vec4::operator == (const float value) {
	return value == x && value == y && value == z && value == w;
}

bool vec4::operator == (const vec4& vector) {
	return vector.x == x && vector.y == y && vector.z == z && vector.w == w;
}

bool vec4::operator != (const vec4& vector) {
	return !(*this == vector);
}


/*
	Function implementation
*/

float structs::lengthSquared(const vec2& vector) {
	return dot(vector, vector);
}

float structs::lengthSquared(const vec3& vector) {
	return dot(vector, vector);
}

float structs::lengthSquared(const vec4& vector) {
	return dot(vector, vector);
}

float structs::length(const vec2& vector) {
	return functions::sqrt(lengthSquared(vector));
}

float structs::length(const vec3& vector) {
	return functions::sqrt(lengthSquared(vector));
}

float structs::length(const vec4& vector) {
	return functions::sqrt(lengthSquared(vector));
}

float structs::invLength(const vec2& vector) {
	return functions::inv_sqrt(lengthSquared(vector));
}

float structs::invLength(const vec3& vector) {
	return functions::inv_sqrt(lengthSquared(vector));
}

float structs::invLength(const vec4& vector) {
	return functions::inv_sqrt(lengthSquared(vector));
}

float structs::dot(const vec2& vectorA, const vec2& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

float structs::dot(const vec3& vectorA, const vec3& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

float structs::dot(const vec4& vectorA, const vec4& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z + vectorA.w * vectorB.w;
}

vec3 structs::cross(const vec3& vectorA, const vec3& vectorB) {
	return vec3(
		vectorA.y * vectorB.z - vectorA.z * vectorB.y,
		vectorA.z * vectorB.x - vectorA.x * vectorB.z,
		vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}

void structs::negate(vec2* vector) {
	for (int i = 0; i < 2; i++)
		(*vector)[i] = -(*vector)[i];
}

void structs::negate(vec3* vector) {
	for (int i = 0; i < 3; i++)
		(*vector)[i] = -(*vector)[i];
}

void structs::negate(vec4* vector) {
	for (int i = 0; i < 4; i++)
		(*vector)[i] = -(*vector)[i];
}

vec2 structs::negate(const vec2& vector) {
	vec2 outVec(vector);
	for (int i = 0; i < 2; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

vec3 structs::negate(const vec3& vector) {
	vec3 outVec(vector);
	for (int i = 0; i < 3; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

vec4 structs::negate(const vec4& vector) {
	vec4 outVec(vector);
	for (int i = 0; i < 4; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

void structs::normalize(vec2* vector) {
	*vector *= functions::inv_sqrt(lengthSquared(*vector));
}

void structs::normalize(vec3* vector) {
	*vector *= functions::inv_sqrt(lengthSquared(*vector));
}

void structs::normalize(vec4* vector) {
	*vector *= functions::inv_sqrt(lengthSquared(*vector));
}

vec2 structs::normalize(const vec2& vector) {
	vec2 outVec(vector);
	return outVec *= functions::inv_sqrt(lengthSquared(vector));
}

vec3 structs::normalize(const vec3& vector) {
	vec3 outVec(vector);
	return outVec *= functions::inv_sqrt(lengthSquared(vector));
}

vec4 structs::normalize(const vec4& vector) {
	vec4 outVec(vector);
	return outVec *= functions::inv_sqrt(lengthSquared(vector));
}

vec2 structs::projection(vec2& vectorA, vec2& vectorB) {
	float factor = vectorA * vectorB / lengthSquared(vectorB);
	vec2 outVec(vectorB);
	return vec2(outVec *= factor);
}

float structs::component(vec2& vectorA, vec2& vectorB) {
	return vectorA * vectorB / length(vectorB);
}