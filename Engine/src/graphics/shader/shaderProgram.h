#pragma once

#ifndef _SHADER_PROGRAM_DEFINED
#define _SHADER_PROGRAM_DEFINED

#define VERTEX_SHADER   0
#define FRAGMENT_SHADER 1
#define COMPUTE_SHADER  2
#define GEOMETRY_SHADER 3

#include <string>

namespace texture {
	class BufferedTexture;
}

namespace shader {

	class Shader {
	public:
		Shader(unsigned int pathCount, const char** shaderPaths);
		~Shader();

		void onProgram();
		void offProgram();

		void dispatch(int groupX, int groupY, int groupZ, int barrier);
		
		operator unsigned int();

	private:
		unsigned int program;
		unsigned int pathCount;
		unsigned int* shaderIds;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

		int workGroupInvocations;

		bool hasDataToCompute = false;
		bool hasImageToCompute = false;

		std::string* shaderSource;

		unsigned int compileShader(unsigned int type, const std::string& source);
		void parseShaderToSource(const char* shaderPath, std::string* shaderSource, unsigned int* type);

	};

	class Uniform {
	public:
		Uniform(unsigned int shaderProgram, const std::string& variableName);

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

		void setMatrix2f(float* matrix2f);
		void setMatrix3f(float* matrix3f);
		void setMatrix4f(float* matrix4f);

	private:
		int location;
		unsigned int shaderProgram;
	};

	class TextureSampler {
	public:
		TextureSampler(int slot, unsigned int shaderProgram, const std::string& variableName);
	private:
		int slot;
		int location;
		unsigned int shaderProgram;
	};

	class ImageBuffer {
	public:
		ImageBuffer(unsigned int imageOffset, unsigned int textureId, int internalFormat);
		~ImageBuffer();

		void bindImageBuffer();

	private:
		unsigned int imageOffset;
		unsigned int textureId;
		int internalFormat;
	};

	class StorageBuffer {
	public:
		StorageBuffer(int bindingOffset, unsigned int size, void* data);
		~StorageBuffer();

		void setData(void* data, int bindingOffset = 0);
		void getData(void* data, int bindingOffset = 0);

		void bind();
		void unbind();

	private:
		int bindingOffset;
		unsigned int ssboId;

	};

}

#endif // !_SHADER_PROGRAM_DEFINED
