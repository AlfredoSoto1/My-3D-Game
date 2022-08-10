#include "maths.h"

#include <math.h>

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

double functions::toDegree(double radian) {
	return (180.0 / PI) * radian;
}

double functions::toRadians(double degree) {
	return (PI / 180.0) * degree;
}

float functions::toDegree(float radian) {
	return (180.0f / PI) * radian;
}

float functions::toRadians(float degree) {
	return (PI / 180.0f) * degree;
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

vec2 vec2::operator + (const vec2& vector) const {
	return vec2(x + vector.x, y + vector.y);
}

vec2 vec2::operator - (const vec2& vector) const {
	return vec2(x - vector.x, y - vector.y);
}

vec2 vec2::operator * (const float factor) const {
	return vec2(x * factor, y * factor);
}

vec2 vec2::operator / (const float factor) const {
	return vec2(x / factor, y / factor);
}

float vec2::operator * (const vec2& vector) const {
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

vec3 vec3::operator + (const vec3& vector) const {
	return vec3(x + vector.x, y + vector.y, z + vector.z);
}

vec3 vec3::operator - (const vec3& vector) const {
	return vec3(x - vector.x, y - vector.y, z - vector.z);
}

vec3 vec3::operator * (const float factor) const {
	return vec3(x * factor, y * factor, z * factor);
}

vec3 vec3::operator / (const float factor) const {
	return vec3(x / factor, y / factor, z / factor);
}

float vec3::operator * (const vec3& vector) const {
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

vec4 vec4::operator + (const vec4& vector) const {
	return vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

vec4 vec4::operator - (const vec4& vector) const {
	return vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

vec4 vec4::operator * (const float factor) const {
	return vec4(x * factor, y * factor, z * factor, w * factor);
}

vec4 vec4::operator / (const float factor) const {
	return vec4(x / factor, y / factor, z / factor, w / factor);
}

float vec4::operator * (const vec4& vector) const {
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

/*
	Matrix implementation
*/

#define ADD  0
#define SUB  1
#define MUL  2
#define DIV  3
#define mMUL 4

mat2::mat2(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat2::mat2(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat2::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat2::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->col];
}

mat2::operator float* () {
	return matrix;
}

vec2 mat2::operator * (const vec2& vector) {
	float x = matrix[0] * vector.x + matrix[1] * vector.y;
	float y = matrix[2] * vector.x + matrix[3] * vector.y;
	return vec2(x, y);
}

mat2::mat2(const mat2& matrix1, const mat2& matrix2, float value, int param) {
	//zero
	for (int i = 0; i < row * col; i++)
		matrix[i] = 0.0;
	//apply arigmethic
	switch (param) {
	case ADD:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
		break;
	case SUB:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] - matrix2.matrix[i];
		break;
	case MUL:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] * value;
		break;
	case DIV:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] / value;
		break;
	case mMUL:
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				float element = 0.0f;
				for (int k = 0; k < row; k++)
					element += matrix1.matrix[k + j * row] * matrix2.matrix[i + k * col];
				matrix[i + j * col] = element;
			}
		break;
	}
}

mat2 mat2::operator + (const mat2& other) {
	return mat2(*this, other, 0, ADD);
}

mat2 mat2::operator - (const mat2& other) {
	return mat2(*this, other, 0, SUB);
}

mat2 mat2::operator * (const mat2& other) {
	return mat2(*this, other, 0, mMUL);
}

mat2 mat2::operator * (float factor) {
	return mat2(*this, *this, factor, MUL);
}

mat2 mat2::operator / (float factor) {
	return mat2(*this, *this, factor, DIV);
}

mat2& mat2::operator += (const mat2& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat2& mat2::operator -= (const mat2& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat2& mat2::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat2& mat2::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat2::operator == (const mat2& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}

/*
	Matrix 3f
*/

mat3::mat3(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat3::mat3(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat3::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat3::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->col];
}

mat3::operator float* () {
	return matrix;
}

vec3 mat3::operator * (const vec3& vector) {
	float x = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z;
	float y = matrix[3] * vector.x + matrix[4] * vector.y + matrix[5] * vector.z;
	float z = matrix[6] * vector.x + matrix[7] * vector.y + matrix[8] * vector.z;
	return vec3(x, y, z);
}

mat3::mat3(const mat3& matrix1, const mat3& matrix2, float value, int param) {
	//zero
	for (int i = 0; i < row * col; i++)
		matrix[i] = 0.0;
	//apply arigmethic
	switch (param) {
	case ADD:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
		break;
	case SUB:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] - matrix2.matrix[i];
		break;
	case MUL:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] * value;
		break;
	case DIV:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] / value;
		break;
	case mMUL:
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				float element = 0.0f;
				for (int k = 0; k < row; k++)
					element += matrix1.matrix[k + j * row] * matrix2.matrix[i + k * col];
				matrix[i + j * col] = element;
			}
		break;
	}
}

mat3 mat3::operator + (const mat3& other) {
	return mat3(*this, other, 0, ADD);
}

mat3 mat3::operator - (const mat3& other) {
	return mat3(*this, other, 0, SUB);
}

mat3 mat3::operator * (const mat3& other) {
	return mat3(*this, other, 0, mMUL);
}

mat3 mat3::operator * (float factor) {
	return mat3(*this, *this, factor, MUL);
}

mat3 mat3::operator / (float factor) {
	return mat3(*this, *this, factor, DIV);
}

mat3& mat3::operator += (const mat3& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat3& mat3::operator -= (const mat3& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat3& mat3::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat3& mat3::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat3::operator == (const mat3& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}

/*
	Matrix 4f
*/

mat4::mat4(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat4::mat4(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat4::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat4::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->row];
}

mat4::operator float* () {
	return matrix;
}

vec4 mat4::operator * (const vec4& vector) {
	float x = matrix[0]  * vector.x + matrix[1]  * vector.y + matrix[2]  * vector.z + matrix[3]  * vector.w;
	float y = matrix[4]  * vector.x + matrix[5]  * vector.y + matrix[6]  * vector.z + matrix[7]  * vector.w;
	float z = matrix[8]  * vector.x + matrix[9]  * vector.y + matrix[10] * vector.z + matrix[11] * vector.w;
	float w = matrix[12] * vector.x + matrix[13] * vector.y + matrix[14] * vector.z + matrix[15] * vector.w;
	return vec4(x, y, z, w);
}

mat4::mat4(const mat4& matrix1, const mat4& matrix2, float value, int param) {
	//zero
	for (int i = 0; i < row * col; i++)
		matrix[i] = 0.0;
	//apply arigmethic
	switch (param) {
	case ADD:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
		break;
	case SUB:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] - matrix2.matrix[i];
		break;
	case MUL:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] * value;
		break;
	case DIV:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] / value;
		break;
	case mMUL:
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				float element = 0.0f;
				for (int k = 0; k < row; k++)
					element += matrix1.matrix[k + j * row] * matrix2.matrix[i + k * col];
				matrix[i + j * col] = element;
			}
		break;
	}
}

mat4 mat4::operator + (const mat4& other) {
	return mat4(*this, other, 0, ADD);
}

mat4 mat4::operator - (const mat4& other) {
	return mat4(*this, other, 0, SUB);
}

mat4 mat4::operator * (const mat4& other) {
	return mat4(*this, other, 0, mMUL);
}

mat4 mat4::operator * (float factor) {
	return mat4(*this, *this, factor, MUL);
}

mat4 mat4::operator / (float factor) {
	return mat4(*this, *this, factor, DIV);
}

mat4& mat4::operator += (const mat4& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat4& mat4::operator -= (const mat4& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat4& mat4::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat4& mat4::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat4::operator == (const mat4& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}

/*
	Matrix functions
*/

void structs::zero(mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = 0.0f;
}

void structs::zero(mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = 0.0f;
}

void structs::zero(mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = 0.0f;
}

void structs::set(float value, mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = value;
}

void structs::set(float value, mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = value;
}

void structs::set(float value, mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = value;
}

void structs::identity(mat2* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void structs::identity(mat3* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void structs::identity(mat4* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void structs::subMatOf(mat3& matrix, unsigned int row, unsigned int col, mat2* out) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != row && col != col) {
				(*out)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

void structs::subMatOf(mat4& matrix, unsigned int row, unsigned int col, mat3* out) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != row && col != col) {
				(*out)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

float structs::determinantOf(mat2& matrix) {
	return matrix[0] * matrix[3] - matrix[1] * matrix[2];
}

float structs::determinantOf(mat3 & matrix) {
	mat2 temp;
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += sign * matrix[i] * determinantOf(temp);
		sign = -sign;
	}
	return determinant;
}

float structs::determinantOf(mat4& matrix) {
	mat3 temp;
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += matrix[i] * determinantOf(temp) * sign;
		sign = -sign;
	}
	return determinant;
}

mat2 structs::transpose(mat2& matrix) {
	mat2 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat3 structs::transpose(mat3& matrix) {
	mat3 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat4 structs::transpose(mat4& matrix) {
	mat4 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat2 structs::inverse(mat2& matrix) {
	mat2 outMatrix;
	outMatrix[0] =  matrix[3];
	outMatrix[1] = -matrix[1];
	outMatrix[2] = -matrix[2];
	outMatrix[3] =  matrix[0];
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

mat3 structs::inverse(mat3& matrix) {
	mat3 adjointMatrix;
	mat2 temp;
	for (int i = 0, sign = 1; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++) {
			subMatOf(matrix, i, j, &temp);
			adjointMatrix[j + i * matrix.col] = determinantOf(temp) * sign;
			sign = -sign;
		}
	mat3 outMatrix = transpose(adjointMatrix);
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

mat4 structs::inverse(mat4& matrix) {
	mat4 adjointMatrix;
	mat3 temp;
	for (int i = 0, sign = 1; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++) {
			subMatOf(matrix, i, j, &temp);
			adjointMatrix[j + i * matrix.col] = determinantOf(temp) * sign;
			sign = -sign;
		}
	mat4 outMatrix = transpose(adjointMatrix);
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

void structs::calcProjectionMatrix(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height) {
	double aspectRatio = width / height;
	double y_scale = (float)(1.0 / tan(maths::functions::toRadians(fov / 2.0)));
	double x_scale = (float)(y_scale / aspectRatio);
	double frustum_length = farDistance - nearDistance;
	projectionMatrix->operator()(0, 0) = (x_scale);
	projectionMatrix->operator()(1, 1) = (y_scale);
	projectionMatrix->operator()(2, 2) = (-((farDistance + nearDistance) / frustum_length));
	projectionMatrix->operator()(2, 3) = (-1);
	projectionMatrix->operator()(3, 2) = (-((2.0 * farDistance * nearDistance) / frustum_length));
	projectionMatrix->operator()(3, 3) = (0);
}


#undef ADD  0
#undef SUB  1
#undef MUL  2
#undef DIV  3
#undef mMUL 4