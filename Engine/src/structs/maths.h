#pragma once

#ifndef _MATHS_DEFINED
#define _MATHS_DEFINED

#define PI 3.14159265359

namespace maths {

	namespace algoritm {
		void quicksort(int length, int* array);

		//returns the quantity of bits given as a parameter: _limit
		unsigned int partOfInt(int number, int limit);
		unsigned long partOfLong(long number, int limit);
		unsigned char partOfByte(char number, int limit);
		unsigned short partOfShort(short number, int limit);
	}

	namespace functions {
		//finds the factorial of an integer number
		int factorial(int number);

		//finds the square root and inverse root of a number
		float sqrt(float number);
		float inv_sqrt(float number);

		double toDegree(double radian);
		double toRadians(double degree);

		float toDegree(float radian);
		float toRadians(float degree);
	}

	namespace structs {

		struct vec2 {
		public:
			float x, y;

			vec2();
			vec2(float xy);
			vec2(float x, float y);
			vec2(const vec2& vector);

			void set(float x, float y);

			float& operator [] (unsigned int index);

			vec2 operator + (const vec2& vector) const;
			vec2 operator - (const vec2& vector) const;
			vec2 operator * (const float factor) const;
			vec2 operator / (const float factor) const;

			float operator * (const vec2& vector) const;

			vec2& operator += (const vec2& vector);
			vec2& operator -= (const vec2& vector);
			vec2& operator *= (const float factor);
			vec2& operator /= (const float factor);

			bool operator == (const float value);
			bool operator == (const vec2& vector);
			bool operator != (const vec2& vector);
		};

		struct vec3 {
		public:
			float x, y, z;

			vec3();
			vec3(float xyz);
			vec3(float x, float y, float z);
			vec3(const vec3& vector);
			vec3(const vec2& vector2, float z);

			void set(float x, float y, float z);

			float& operator [] (unsigned int index);

			vec3 operator + (const vec3& vector) const;
			vec3 operator - (const vec3& vector) const;
			vec3 operator * (const float factor) const;
			vec3 operator / (const float factor) const;

			vec3& operator += (const vec3& vector);
			vec3& operator -= (const vec3& vector);
			vec3& operator *= (const float factor);
			vec3& operator /= (const float factor);

			float operator * (const vec3& vector) const;

			vec3 operator | (const vec3& vector);

			bool operator == (const float value);
			bool operator == (const vec3& vector);
			bool operator != (const vec3& vector);
		};

		struct vec4 {
		public:
			float x, y, z, w;

			vec4();
			vec4(const vec4& vector);
			vec4(const vec3& vector3, float w);
			vec4(const vec2& vector2, float z, float w);
			vec4(float x, float y, float z, float w);
			vec4(float xyzw);

			void set(float x, float y, float z, float w);

			float& operator [] (unsigned int index);

			vec4 operator + (const vec4& vector) const;
			vec4 operator - (const vec4& vector) const;
			vec4 operator * (const float factor) const;
			vec4 operator / (const float factor) const;

			float operator * (const vec4& vector) const;

			vec4& operator += (const vec4& vector);
			vec4& operator -= (const vec4& vector);
			vec4& operator *= (const float factor);
			vec4& operator /= (const float factor);

			bool operator == (const float value);
			bool operator == (const vec4& vector);
			bool operator != (const vec4& vector);
		};

		/*
			Vector functions
		*/
		float lengthSquared(const vec2& vector);
		float lengthSquared(const vec3& vector);
		float lengthSquared(const vec4& vector);

		float length(const vec2& vector);
		float length(const vec3& vector);
		float length(const vec4& vector);

		float invLength(const vec2& vector);
		float invLength(const vec3& vector);
		float invLength(const vec4& vector);

		float dot(const vec2& vector1, const vec2& vector2);
		float dot(const vec3& vector1, const vec3& vector2);
		float dot(const vec4& vector1, const vec4& vector2);

		vec3 cross(const vec3& vector1, const vec3& vector2);

		void negate(vec2* vector);
		void negate(vec3* vector);
		void negate(vec4* vector);

		vec2 negate(const vec2& vector);
		vec3 negate(const vec3& vector);
		vec4 negate(const vec4& vector);

		void normalize(vec2* vector);
		void normalize(vec3* vector);
		void normalize(vec4* vector);

		vec2 normalize(const vec2& vector);
		vec3 normalize(const vec3& vector);
		vec4 normalize(const vec4& vector);

		vec2 projection(vec2& vector1, vec2& vector2);
		float component(vec2& vector1, vec2& vector2);

		/*
			Matrix
		*/

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

			operator float*();

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

		void subMatOf(mat3& matrix, unsigned int row, unsigned int col, mat2* out);
		void subMatOf(mat4& matrix, unsigned int row, unsigned int col, mat3* out);

		float determinantOf(mat2& matrix);
		float determinantOf(mat3& matrix);
		float determinantOf(mat4& matrix);

		mat2 transpose(mat2& matrix);
		mat3 transpose(mat3& matrix);
		mat4 transpose(mat4& matrix);

		mat2 inverse(mat2& matrix);
		mat3 inverse(mat3& matrix);
		mat4 inverse(mat4& matrix);

		void calcProjectionMatrix(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height);

	}
}
#endif // !_MATHS_DEFINED