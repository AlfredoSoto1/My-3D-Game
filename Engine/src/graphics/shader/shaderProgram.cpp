#include "shaderProgram.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <iostream>

#include "../textures/bufferedTexture.h"

using namespace shader;

Shader::Shader(unsigned int pathCount, const char** shaderPaths)
	: pathCount(pathCount)
{
	program = glCreateProgram();

	shaderIds = new unsigned int[pathCount];
	shaderSource = new std::string[pathCount];

	unsigned int type = GL_COMPUTE_SHADER;
	for (int i = 0; i < pathCount; i++) {
		parseShaderToSource(shaderPaths[i], &shaderSource[i], &type);
		if (shaderSource[i].length() != 0) {
			shaderIds[i] = compileShader(type, shaderSource[i]);
			glAttachShader(program, shaderIds[i]);
		}
	}

	if (type == GL_COMPUTE_SHADER && pathCount == 1) {
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workGroupMaxCount[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workGroupMaxCount[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workGroupMaxCount[2]);

		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workGroupMaxSize[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workGroupMaxSize[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workGroupMaxSize[2]);

		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workGroupInvocations);
	}
	
	if (pathCount == 0)
		return;

	glLinkProgram(program);
	glValidateProgram(program);
}

Shader::~Shader() {
	for (int i = 0; i < pathCount; i++) {
		if (shaderSource[i].length() != 0) {
			glDetachShader(program, shaderIds[i]);
			glDeleteShader(shaderIds[i]);
		}
	}
	glDeleteProgram(program);

	delete[] shaderIds;
	delete[] shaderSource;
}

void Shader::onProgram() {
	glUseProgram(program);
}

void Shader::offProgram() {
	glUseProgram(0);
}

void Shader::dispatch(int groupX, int groupY, int groupZ, int barrier) {
	//GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT <-- barrier
	glUseProgram(program);
	glDispatchCompute(
		groupX > workGroupMaxCount[0] ? workGroupMaxCount[0] : groupX,
		groupY > workGroupMaxCount[1] ? workGroupMaxCount[1] : groupY,
		groupZ > workGroupMaxCount[2] ? workGroupMaxCount[2] : groupZ);

	glMemoryBarrier(barrier);
	glUseProgram(0);
}

Shader::operator unsigned int() {
	return program;
}

void Shader::parseShaderToSource(const char* shaderPath, std::string* shaderSource, unsigned int* type) {
	if (shaderPath == nullptr)
		return;//return if no other shader is being parsed

	std::ifstream fileStream;
	fileStream.open(shaderPath, std::ios::in);
	std::stringstream stream;

	//first checks if file can be opened
	if (fileStream.is_open()) {
		bool shaderTypeFound = false;
		std::string line;
		//reads line by line
		while (getline(fileStream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					*type = GL_VERTEX_SHADER;
				else if (line.find("fragment") != std::string::npos)
					*type = GL_FRAGMENT_SHADER;
				else if (line.find("geometry") != std::string::npos)
					*type = GL_GEOMETRY_SHADER;
				else if (line.find("compute") != std::string::npos)
					*type = GL_COMPUTE_SHADER;
				else
					std::cout << "Shader type " << line << "\nis not defined in: " << shaderPath << std::endl;
				shaderTypeFound = true;
			}
			else {
				if(!shaderTypeFound)
					std::cout << "Shader type is not defined in: " << shaderPath << std::endl;
				stream << line << "\n";
			}
		}
		//it merges the new file in string format to output string
		shaderSource->append(stream.str());
		fileStream.close();
	}
	else {
		std::cout << "File at " << shaderPath << " \nwas not found." << std::endl;
	}
}

unsigned int Shader::compileShader(unsigned int type, const std::string& shaderSource) {
	//Shader source must be a string allocated in the heap
	unsigned int shaderId = glCreateShader(type);
	const char* src = &(shaderSource.c_str())[0];
	glShaderSource(shaderId, 1, &src, nullptr);
	glCompileShader(shaderId);

	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int messageLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);
		char* message = (char*)alloca(messageLength * sizeof(char));
		glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);

		const char* shaderType = nullptr;
		switch (type) {
		case GL_VERTEX_SHADER:
			shaderType = "Vertex Shader";
			break;
		case GL_FRAGMENT_SHADER:
			shaderType = "Fragment Shader";
			break;
		case GL_COMPUTE_SHADER:
			shaderType = "Compute Shader";
			break;
		case GL_GEOMETRY_SHADER:
			shaderType = "Geometry Shader";
			break;
		}
		std::cout << "[Failed to compile shader] <type: " << shaderType << ">\n" << message << std::endl;
		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}

/*
	Uniform
*/

Uniform::Uniform(unsigned int shaderProgram, const std::string& variableName) :
	shaderProgram(shaderProgram)
{
	location = glGetUniformLocation(shaderProgram, variableName.c_str());
}

void Uniform::setFloat1(const float& x) {
	glUniform1f(location, x);
}

void Uniform::setFloat2(const float& x, const float& y) {
	glUniform2f(location, x, y);
}

void Uniform::setFloat3(const float& x, const float& y, const float& z) {
	glUniform3f(location, x, y, z);
}

void Uniform::setFloat4(const float& x, const float& y, const float& z, const float& w) {
	glUniform4f(location, x, y, z, w);
}

void Uniform::setDouble1(const double& x) {
	glUniform1d(location, x);
}

void Uniform::setDouble2(const double& x, const double& y) {
	glUniform2d(location, x, y);
}

void Uniform::setDouble3(const double& x, const double& y, const double& z) {
	glUniform3d(location, x, y, z);
}

void Uniform::setDouble4(const double& x, const double& y, const double& z, const double &w) {
	glUniform4d(location, x, y, z, w);
}

void Uniform::setInt1(const int& x) {
	glUniform1i(location, x);
}

void Uniform::setInt2(const int& x, const int& y) {
	glUniform2i(location, x, y);
}

void Uniform::setInt3(const int& x, const int& y, const int& z) {
	glUniform3i(location, x, y, z);
}

void Uniform::setInt4(const int& x, const int& y, const int& z, const int& w) {
	glUniform4i(location, x, y, z, w);
}

void Uniform::setUInt1(const unsigned int& x) {
	glUniform1ui(location, x);
}

void Uniform::setUInt2(const unsigned int& x, const unsigned int& y) {
	glUniform2ui(location, x, y);
}

void Uniform::setUInt3(const unsigned int& x, const unsigned int& y, const unsigned int& z) {
	glUniform3ui(location, x, y, z);
}

void Uniform::setUInt4(const unsigned int& x, const unsigned int& y, const unsigned int& z, const unsigned int& w) {
	glUniform4i(location, x, y, z, w);
}

void Uniform::setMatrix2f(float* matrix2f) {
	glUniformMatrix2fv(location, 1, GL_TRUE, matrix2f);
}

void Uniform::setMatrix3f(float* matrix3f) {
	glUniformMatrix3fv(location, 1, GL_TRUE, matrix3f);
}

void Uniform::setMatrix4f(float* matrix4f) {
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix4f);
}

/*
	Texture Sampler Uniform
*/

TextureSampler::TextureSampler(int slot, unsigned int shaderProgram, const std::string& variableName) :
	shaderProgram(shaderProgram)
{
	location = glGetUniformLocation(shaderProgram, variableName.c_str());

	glUseProgram(shaderProgram);
	glUniform1i(location, slot);
	glUseProgram(0);
}

/*
	Image Buffer
*/

ImageBuffer::ImageBuffer(unsigned int imageOffset, unsigned int textureId, int internalFormat) 
	: imageOffset(imageOffset), textureId(textureId), internalFormat(internalFormat)
{

}

ImageBuffer::~ImageBuffer() {

}

void ImageBuffer::bindImageBuffer() {
	glBindImageTexture(imageOffset, textureId, 0, GL_FALSE, 0, GL_WRITE_ONLY, internalFormat);
}

/*
	Storage Buffer Object
*/

StorageBuffer::StorageBuffer(int bindingOffset, unsigned int size, void* data)
	: bindingOffset(bindingOffset)
{
	glGenBuffers(1, &ssboId);
	bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingOffset, ssboId);
	unbind();
}

StorageBuffer::~StorageBuffer() {
	glDeleteBuffers(1, &ssboId);
}

void StorageBuffer::setData(void* data, int bindingOffset) {
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, bindingOffset, sizeof(data), data);
}

void StorageBuffer::getData(void* data, int bindingOffset) {
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, bindingOffset, sizeof(data), data);
}

void StorageBuffer::bind() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboId);
}

void StorageBuffer::unbind() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}