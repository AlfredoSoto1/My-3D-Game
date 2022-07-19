#pragma once

#ifndef _MESH_DEFINED
#define _MESH_DEFINED

namespace geometry {

	class Mesh {
	public:

		Mesh();
		~Mesh();

		unsigned int getVao() const;
		unsigned int getIbo() const;
		unsigned int getIndexCount() const;

		void bind() const;
		void unbind() const;

		void createIndexBuffer(int length, unsigned int* data);
		void createAttribute(unsigned int location, int dimension, int length, void* data, unsigned int type);

	private:

		unsigned int vao;
		unsigned int ibo;
		unsigned int indexCount;

		bool hasIbo = false;

		void* vboList;
		void* attribNumberList;
	};

}

#endif // !_MESH_DEFINED
