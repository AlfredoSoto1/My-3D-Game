#pragma once

#ifndef _MATHS_DEFINED
#define _MATHS_DEFINED

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

			vec2 operator + (const vec2& vector);
			vec2 operator - (const vec2& vector);
			vec2 operator * (const float factor);
			vec2 operator / (const float factor);

			float operator * (const vec2& vector);

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

			vec3 operator + (const vec3& vector);
			vec3 operator - (const vec3& vector);
			vec3 operator * (const float factor);
			vec3 operator / (const float factor);

			vec3& operator += (const vec3& vector);
			vec3& operator -= (const vec3& vector);
			vec3& operator *= (const float factor);
			vec3& operator /= (const float factor);

			float operator * (const vec3& vector);

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

			vec4 operator + (const vec4& vector);
			vec4 operator - (const vec4& vector);
			vec4 operator * (const float factor);
			vec4 operator / (const float factor);

			float operator * (const vec4& vector);

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
	}
}
#endif // !_MATHS_DEFINED