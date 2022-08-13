#pragma once

#ifndef _MATRIX_DEFINED
#define _MATRIX_DEFINED

#include "vectors.h"

namespace maths {
	struct mat2 {
	public:
		static const unsigned int row = 2;
		static const unsigned int col = 2;

		mat2(float value = 0.0f);
		mat2(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec2 operator * (const vec2& vector);

		mat2 operator + (const mat2& other);
		mat2 operator - (const mat2& other);
		mat2 operator * (const mat2& other);
		mat2 operator * (float factor);
		mat2 operator / (float factor);

		mat2& operator += (const mat2& other);
		mat2& operator -= (const mat2& other);
		mat2& operator *= (float factor);
		mat2& operator /= (float factor);

		bool operator == (const mat2& other);

	private:
		float matrix[row * col];
		mat2(const mat2& matrix1, const mat2& matrix2, float value, int param);
	};

	struct mat3 {
	public:
		static const int row = 3;
		static const int col = 3;

		mat3(float value = 0.0f);
		mat3(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec3 operator * (const vec3& vector);

		mat3 operator + (const mat3& other);
		mat3 operator - (const mat3& other);
		mat3 operator * (const mat3& other);
		mat3 operator * (float factor);
		mat3 operator / (float factor);

		mat3& operator += (const mat3& other);
		mat3& operator -= (const mat3& other);
		mat3& operator *= (float factor);
		mat3& operator /= (float factor);

		bool operator == (const mat3& other);

	private:
		float matrix[row * col];
		mat3(const mat3& matrix1, const mat3& matrix2, float value, int param);
	};

	struct mat4 {
	public:
		static const int row = 4;
		static const int col = 4;

		mat4(float value = 0.0f);
		mat4(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec4 operator * (const vec4& vector);

		mat4 operator + (const mat4& other);
		mat4 operator - (const mat4& other);
		mat4 operator * (const mat4& other);
		mat4 operator * (float factor);
		mat4 operator / (float factor);

		mat4& operator += (const mat4& other);
		mat4& operator -= (const mat4& other);
		mat4& operator *= (float factor);
		mat4& operator /= (float factor);

		bool operator == (const mat4& other);

	private:
		float matrix[row * col];
		mat4(const mat4& matrix1, const mat4& matrix2, float value, int param);
	};

	/*
		Matrix functions
	*/

	void zero(mat2* matrix);
	void zero(mat3* matrix);
	void zero(mat4* matrix);

	void set(float value, mat2* matrix);
	void set(float value, mat3* matrix);
	void set(float value, mat4* matrix);

	void identity(mat2* matrix);
	void identity(mat3* matrix);
	void identity(mat4* matrix);

	void subMatOf(mat3& matrix, unsigned int row, unsigned int col, mat2* dest);
	void subMatOf(mat4& matrix, unsigned int row, unsigned int col, mat3* dest);

	float determinantOf(mat2& matrix);
	float determinantOf(mat3& matrix);
	float determinantOf(mat4& matrix);

	mat2 transpose(mat2& matrix);
	mat3 transpose(mat3& matrix);
	mat4 transpose(mat4& matrix);

	mat2 inverse(mat2& matrix);
	mat3 inverse(mat3& matrix);
	mat4 inverse(mat4& matrix);

	void rotate(mat4& src, mat4* dest, float angle, const vec3& axis);

	void scale(mat4& src, mat4* dest, const vec3& scaleVector);
	void translate(mat4& src, mat4* dest, const vec3& position);

	void project(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height);

	void transform(mat4* transformationMatrix, const vec3& position, const vec3& rotation, const vec3& scale);

}

#endif // !_MATRIX_DEFINED
