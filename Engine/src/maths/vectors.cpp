#include "vectors.h"
#include "functions.h"
#include "constants.h"

using namespace maths;

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float xy) : x(xy), y(xy) {}
vec2::vec2(float x, float y) : x(x), y(y) {}
vec2::vec2(const vec2& vector) : x(vector.x), y(vector.y) {}

void vec2::set(float x, float y) {
	this->x = x;
	this->y = y;
}

float& vec2::operator [] (unsigned int index) {
	return *((float*)this + index);
}

vec2 vec2::operator - () {
	return vec2(-x, -y);
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
	return *((float*)this + index);
}

vec3 vec3::operator - () {
	return vec3(-x, -y, -z);
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
	return *((float*)this + index);
}

vec4 vec4::operator - () {
	return vec4(-x, -y, -z, -w);
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

float maths::lengthSquared(const vec2& vector) {
	return dot(vector, vector);
}

float maths::lengthSquared(const vec3& vector) {
	return dot(vector, vector);
}

float maths::lengthSquared(const vec4& vector) {
	return dot(vector, vector);
}

float maths::length(const vec2& vector) {
	return maths::sqrt(lengthSquared(vector));
}

float maths::length(const vec3& vector) {
	return maths::sqrt(lengthSquared(vector));
}

float maths::length(const vec4& vector) {
	return maths::sqrt(lengthSquared(vector));
}

float maths::invLength(const vec2& vector) {
	return maths::inv_sqrt(lengthSquared(vector));
}

float maths::invLength(const vec3& vector) {
	return maths::inv_sqrt(lengthSquared(vector));
}

float maths::invLength(const vec4& vector) {
	return maths::inv_sqrt(lengthSquared(vector));
}

float maths::dot(const vec2& vectorA, const vec2& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

float maths::dot(const vec3& vectorA, const vec3& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

float maths::dot(const vec4& vectorA, const vec4& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z + vectorA.w * vectorB.w;
}

vec3 maths::cross(const vec3& vectorA, const vec3& vectorB) {
	return vec3(
		vectorA.y * vectorB.z - vectorA.z * vectorB.y,
		vectorA.z * vectorB.x - vectorA.x * vectorB.z,
		vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}

void maths::negate(vec2* vector) {
	for (int i = 0; i < 2; i++)
		(*vector)[i] = -(*vector)[i];
}

void maths::negate(vec3* vector) {
	for (int i = 0; i < 3; i++)
		(*vector)[i] = -(*vector)[i];
}

void maths::negate(vec4* vector) {
	for (int i = 0; i < 4; i++)
		(*vector)[i] = -(*vector)[i];
}

vec2 maths::negate(const vec2& vector) {
	vec2 outVec(vector);
	for (int i = 0; i < 2; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

vec3 maths::negate(const vec3& vector) {
	vec3 outVec(vector);
	for (int i = 0; i < 3; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

vec4 maths::negate(const vec4& vector) {
	vec4 outVec(vector);
	for (int i = 0; i < 4; i++)
		outVec[i] = -outVec[i];
	return outVec;
}

void maths::normalize(vec2* vector) {
	*vector *= maths::inv_sqrt(lengthSquared(*vector));
}

void maths::normalize(vec3* vector) {
	*vector *= maths::inv_sqrt(lengthSquared(*vector));
}

void maths::normalize(vec4* vector) {
	*vector *= maths::inv_sqrt(lengthSquared(*vector));
}

vec2 maths::normalize(const vec2& vector) {
	vec2 outVec(vector);
	return outVec *= maths::inv_sqrt(lengthSquared(vector));
}

vec3 maths::normalize(const vec3& vector) {
	vec3 outVec(vector);
	return outVec *= maths::inv_sqrt(lengthSquared(vector));
}

vec4 maths::normalize(const vec4& vector) {
	vec4 outVec(vector);
	return outVec *= maths::inv_sqrt(lengthSquared(vector));
}

vec2 maths::projection(vec2& vectorA, vec2& vectorB) {
	float factor = vectorA * vectorB / lengthSquared(vectorB);
	vec2 outVec(vectorB);
	return vec2(outVec *= factor);
}

float maths::component(vec2& vectorA, vec2& vectorB) {
	return vectorA * vectorB / length(vectorB);
}

vec3 maths::getNormal(const vec3& point1, const vec3& point2, const vec3& point3) {
	return cross(point2 - point1, point3 - point1);
}