#include "shaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include <GL/glew.h>

using namespace shader;

const char* ShaderProgram::VERTEX_DEFAULT_LOCATION = "src/graphics/shader/defaultVertex.shader";
const char* ShaderProgram::FRAGMENT_DEFAULT_LOCATION = "src/graphics/shader/defaultFragment.shader";

void ShaderProgram::parseShader(const char* _inShaderPath, std::string* _outShaderString) {
	if (_inShaderPath == nullptr)
		return;//return if no other shader is being parsed

	std::ifstream fileStream;
	fileStream.open(_inShaderPath, std::ios::in);
	std::stringstream stream;

	//first checks if file can be opened
	if (fileStream.is_open()) {
		std::string line;
		//reads line by line
		while (getline(fileStream, line))
			stream << line << "\n";
		//it merges the new file in string format to output string
		_outShaderString->append(stream.str());
		fileStream.close();
	}
	else {
		std::cout << "File at " << _inShaderPath << " \nwas not found." << std::endl;
	}
}

unsigned int ShaderProgram::compileShader(unsigned int _type, const std::string& _source) {
	//Shader source must be a string allocated in the heap
	unsigned int shaderId = glCreateShader(_type);
	const char* src = &(_source.c_str())[0];
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
		switch (_type) {
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

void ShaderProgram::createShader(const char* _vertLocation, const char* _fragLocation, const char* _geomLocation, const char* _compLocation) {
	program = glCreateProgram();

	//check if there is no shader so that machine uses default shader built
	if (_vertLocation == nullptr)
		_vertLocation = ShaderProgram::VERTEX_DEFAULT_LOCATION;
	if (_fragLocation == nullptr)
		_fragLocation = ShaderProgram::FRAGMENT_DEFAULT_LOCATION;

	//parse shader from file to string
	parseShader(_vertLocation, &vertex);
	parseShader(_fragLocation, &fragment);
	parseShader(_geomLocation, &geometry);
	parseShader(_compLocation, &compute);

	//compile shader and attach
	if (vertex.length() != 0) {
		this->vertShader = compileShader(GL_VERTEX_SHADER, vertex);
		glAttachShader(program, vertShader);
	}
	if (fragment.length() != 0) {
		this->fragShader = compileShader(GL_FRAGMENT_SHADER, fragment);
		glAttachShader(program, fragShader);
	}
	if (geometry.length() != 0) {
		this->geomShader = compileShader(GL_GEOMETRY_SHADER, geometry);
		glAttachShader(program, geomShader);
	}
	if (compute.length() != 0) {
		this->compShader = compileShader(GL_COMPUTE_SHADER, compute);
		glAttachShader(program, compShader);
	}

	hasCreatedShader = true;
	//glBindAttribLocation(program, 0, "position");

	glLinkProgram(program);
	glValidateProgram(program);

	//find uniform location
}

void ShaderProgram::deleteShader() {
	//detaches each shader and deletes it
	if (vertex.length() != 0) {
		glDetachShader(program, vertShader);
		glDeleteShader(vertShader);
	}
	if (fragment.length() != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
	}
	if (geometry.length() != 0) {
		glDetachShader(program, geomShader);
		glDeleteShader(geomShader);
	}
	if (compute.length() != 0) {
		glDetachShader(program, compShader);
		glDeleteShader(compShader);
	}
	//deletes shader program
	glDeleteProgram(program);
}