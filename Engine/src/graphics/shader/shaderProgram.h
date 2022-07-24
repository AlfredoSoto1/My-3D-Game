#pragma once

#ifndef _SHADER_PROGRAM_DEFINED
#define _SHADER_PROGRAM_DEFINED

#define VERTEX_SHADER   0
#define FRAGMENT_SHADER 1
#define COMPUTE_SHADER  2
#define GEOMETRY_SHADER 3

#include <string>

namespace shader {

	class Shader {
	public:
		Shader(unsigned int pathCount, const char** shaderPaths);
		~Shader();

		void onProgram();
		void offProgram();
		
		operator unsigned int();
	private:
		unsigned int program;
		unsigned int pathCount;
		unsigned int* shaderIds;

		std::string* shaderSource;

		unsigned int compileShader(unsigned int type, const std::string& source);
		void parseShaderToSource(const char* shaderPath, std::string* shaderSource, unsigned int* type);
	};

	class Uniform {
	public:
		Uniform(const std::string& variableName, unsigned int shaderProgram);

		void setFloat1(const float& x);
		void setFloat2(const float& x, const float& y);
		void setFloat3(const float& x, const float& y, const float& z);
		void setFloat4(const float& x, const float& y, const float& z, const float& w);

		void setDouble1(const double& x);
		void setDouble2(const double& x, const double& y);
		void setDouble3(const double& x, const double& y, const double& z);
		void setDouble4(const double& x, const double& y, const double& z, const double& w);

		void setInt1(const int& x);
		void setInt2(const int& x, const int& y);
		void setInt3(const int& x, const int& y, const int& z);
		void setInt4(const int& x, const int& y, const int& z, const int& w);
		
		void setUInt1(const unsigned int& x);
		void setUInt2(const unsigned int& x, const unsigned int& y);
		void setUInt3(const unsigned int& x, const unsigned int& y, const unsigned int& z);
		void setUInt4(const unsigned int& x, const unsigned int& y, const unsigned int& z, const unsigned int& w);

	private:
		int location;
		unsigned int shaderProgram;
	};
}

#endif // !_SHADER_PROGRAM_DEFINED
