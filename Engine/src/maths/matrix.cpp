#include "matrix.h"
#include "vectors.h"
#include "functions.h"
#include "constants.h"

#include <math.h>

using namespace maths;

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
	float x = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z + matrix[3] * vector.w;
	float y = matrix[4] * vector.x + matrix[5] * vector.y + matrix[6] * vector.z + matrix[7] * vector.w;
	float z = matrix[8] * vector.x + matrix[9] * vector.y + matrix[10] * vector.z + matrix[11] * vector.w;
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


void maths::zero(mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = 0.0f;
}

void maths::zero(mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = 0.0f;
}

void maths::zero(mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = 0.0f;
}

void maths::set(float value, mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = value;
}

void maths::set(float value, mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = value;
}

void maths::set(float value, mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = value;
}

void maths::identity(mat2* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void maths::identity(mat3* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void maths::identity(mat4* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void maths::subMatOf(mat3& matrix, unsigned int row, unsigned int col, mat2* dest) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != row && col != col) {
				(*dest)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

void maths::subMatOf(mat4& matrix, unsigned int _row, unsigned int _col, mat3* dest) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != _row && col != _col) {
				(*dest)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

float maths::determinantOf(mat2& matrix) {
	return matrix[0] * matrix[3] - matrix[1] * matrix[2];
}

float maths::determinantOf(mat3& matrix) {
	mat2 temp;
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += sign * matrix[i] * determinantOf(temp);
		sign = -sign;
	}
	return determinant;
}

float maths::determinantOf(mat4& matrix) {
	mat3 temp;
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += matrix[i] * determinantOf(temp) * sign;
		sign = -sign;
	}
	return determinant;
}

mat2 maths::transpose(mat2& matrix) {
	mat2 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat3 maths::transpose(mat3& matrix) {
	mat3 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat4 maths::transpose(mat4& matrix) {
	mat4 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat2 maths::inverse(mat2& matrix) {
	mat2 outMatrix;
	outMatrix[0] = matrix[3];
	outMatrix[1] = -matrix[1];
	outMatrix[2] = -matrix[2];
	outMatrix[3] = matrix[0];
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

mat3 maths::inverse(mat3& matrix) {
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

mat4 maths::inverse(mat4& matrix) {
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

void maths::project(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height) {
	double aspectRatio = width / height;
	double y_scale = (float)(1.0 / tan(maths::toRadians(fov / 2.0)));
	double x_scale = (float)(y_scale / aspectRatio);
	double frustum_length = farDistance - nearDistance;
	projectionMatrix->operator()(0, 0) = (x_scale);
	projectionMatrix->operator()(1, 1) = (y_scale);
	projectionMatrix->operator()(2, 2) = (-((farDistance + nearDistance) / frustum_length));
	projectionMatrix->operator()(2, 3) = (-1);
	projectionMatrix->operator()(3, 2) = (-((2.0 * farDistance * nearDistance) / frustum_length));
	projectionMatrix->operator()(3, 3) = (0);
}

void maths::rotate(mat4& src, mat4* dest, float angle, const vec3& axis) {
	float c = cos(angle);
	float s = sin(angle);
	float oneminusc = 1.0f - c;
	float xy = axis.x * axis.y;
	float yz = axis.y * axis.z;
	float xz = axis.x * axis.z;
	float xs = axis.x * s;
	float ys = axis.y * s;
	float zs = axis.z * s;

	float f00 = axis.x * axis.x * oneminusc + c;
	float f01 = xy * oneminusc + zs;
	float f02 = xz * oneminusc - ys;
	// n[3] not used
	float f10 = xy * oneminusc - zs;
	float f11 = axis.y * axis.y * oneminusc + c;
	float f12 = yz * oneminusc + xs;
	// n[7] not used
	float f20 = xz * oneminusc + ys;
	float f21 = yz * oneminusc - xs;
	float f22 = axis.z * axis.z * oneminusc + c;

	float t00 = src(0, 0) * f00 + src(1, 0) * f01 + src(2, 0) * f02;
	float t01 = src(0, 1) * f00 + src(1, 1) * f01 + src(2, 1) * f02;
	float t02 = src(0, 2) * f00 + src(1, 2) * f01 + src(2, 2) * f02;
	float t03 = src(0, 3) * f00 + src(1, 3) * f01 + src(2, 3) * f02;
	float t10 = src(0, 0) * f10 + src(1, 0) * f11 + src(2, 0) * f12;
	float t11 = src(0, 1) * f10 + src(1, 1) * f11 + src(2, 1) * f12;
	float t12 = src(0, 2) * f10 + src(1, 2) * f11 + src(2, 2) * f12;
	float t13 = src(0, 3) * f10 + src(1, 3) * f11 + src(2, 3) * f12;
	(*dest)(2, 0) = src(0, 0) * f20 + src(1, 0) * f21 + src(2, 0) * f22;
	(*dest)(2, 1) = src(0, 1) * f20 + src(1, 1) * f21 + src(2, 1) * f22;
	(*dest)(2, 2) = src(0, 2) * f20 + src(1, 2) * f21 + src(2, 2) * f22;
	(*dest)(2, 3) = src(0, 3) * f20 + src(1, 3) * f21 + src(2, 3) * f22;
	(*dest)(0, 0) = t00;
	(*dest)(0, 1) = t01;
	(*dest)(0, 2) = t02;
	(*dest)(0, 3) = t03;
	(*dest)(1, 0) = t10;
	(*dest)(1, 1) = t11;
	(*dest)(1, 2) = t12;
	(*dest)(1, 3) = t13;
}

void maths::scale(mat4& src, mat4* dest, const vec3& scaleVector) {
	(*dest)(0, 0) = src(0, 0) * scaleVector.x;
	(*dest)(0, 1) = src(0, 1) * scaleVector.x;
	(*dest)(0, 2) = src(0, 2) * scaleVector.x;
	(*dest)(0, 3) = src(0, 3) * scaleVector.x;
	(*dest)(1, 0) = src(1, 0) * scaleVector.y;
	(*dest)(1, 1) = src(1, 1) * scaleVector.y;
	(*dest)(1, 2) = src(1, 2) * scaleVector.y;
	(*dest)(1, 3) = src(1, 3) * scaleVector.y;
	(*dest)(2, 0) = src(2, 0) * scaleVector.z;
	(*dest)(2, 1) = src(2, 1) * scaleVector.z;
	(*dest)(2, 2) = src(2, 2) * scaleVector.z;
	(*dest)(2, 3) = src(2, 3) * scaleVector.z;
}

void maths::translate(mat4& src, mat4* dest, const vec3& position) {
	(*dest)(3, 0) += src(0, 0) * position.x + src(1, 0) * position.y + src(2, 0) * position.z;
	(*dest)(3, 1) += src(0, 1) * position.x + src(1, 1) * position.y + src(2, 1) * position.z;
	(*dest)(3, 2) += src(0, 2) * position.x + src(1, 2) * position.y + src(2, 2) * position.z;
	(*dest)(3, 3) += src(0, 3) * position.x + src(1, 3) * position.y + src(2, 3) * position.z;
}

void maths::transform(mat4* transformationMatrix, const vec3& position, const vec3& rotation, const vec3& scaleVector) {
	identity(transformationMatrix);
	//apply translation
	translate(*transformationMatrix, transformationMatrix, position);
	//apply rotation
	rotate(*transformationMatrix, transformationMatrix, rotation.x, vec3(1.0, 0.0, 0.0));
	rotate(*transformationMatrix, transformationMatrix, rotation.y, vec3(0.0, 1.0, 0.0));
	rotate(*transformationMatrix, transformationMatrix, rotation.z, vec3(0.0, 0.0, 1.0));
	//apply scale
	scale(*transformationMatrix, transformationMatrix, scaleVector);
}

#undef ADD  0
#undef SUB  1
#undef MUL  2
#undef DIV  3
#undef mMUL 4