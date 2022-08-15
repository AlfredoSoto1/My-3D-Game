#pragma once

#ifndef _VERTEX_BUFFER_DEFINED
#define _VERTEX_BUFFER_DEFINED

#include "../maths/vectors.h"

namespace buffer {

	struct Vertex {
		maths::vec3 position;
		maths::vec3 normal;
		unsigned int index;

		bool operator == (const Vertex& vertex) {
			bool samePosition = position == vertex.position;
			bool sameNormal = normal == vertex.normal;
			return samePosition && sameNormal;
		}
	};

	class VertexBuffer {
	public:
		VertexBuffer(unsigned int resizeStep);
		~VertexBuffer();

		void add(const Vertex& vertex);
		void remove(unsigned int location);
		void remove(const Vertex& vertex);
		void replace(unsigned int location, const Vertex& newVertex);
		void replace(const Vertex& oldVertex, const Vertex& newVertex);

		//temp
		Vertex* get(unsigned int location);

		bool isEmpty() const;
		bool contains(const Vertex& vertex);

		unsigned int getCount() const;
		void clear();

	private:
		unsigned int vertexCounter;
		unsigned int bufferLength;
		unsigned int resizeStep;

		Vertex* data;

		int find(const Vertex& vertex);

		void resize();
		bool needToResize();
	};

}

#endif // !_VERTEX_BUFFER_DEFINED
