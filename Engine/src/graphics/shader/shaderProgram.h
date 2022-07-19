#pragma once


#ifndef _SHADER_PROGRAM_DEFINED
#define _SHADER_PROGRAM_DEFINED

#include <string>

namespace shader {

	class ShaderProgram {
	private:
		static const char* VERTEX_DEFAULT_LOCATION;
		static const char* FRAGMENT_DEFAULT_LOCATION;

		std::string vertex;
		std::string fragment;
		std::string geometry;
		std::string compute;

		unsigned int vertShader;
		unsigned int fragShader;
		unsigned int geomShader;
		unsigned int compShader;

		unsigned int compileShader(unsigned int, const std::string&);

		void parseShader(const char*, std::string*);

		bool hasCreatedShader = false;

	public:
		unsigned int program;

		void createShader(const char*, const char*, const char*, const char*);
		void deleteShader();
	};
}

#endif // !_SHADER_PROGRAM_DEFINED
