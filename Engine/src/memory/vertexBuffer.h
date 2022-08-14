#pragma once

namespace buffer {

	struct Vertex;

	class VertexBuffer {
	public:
		VertexBuffer(unsigned int resizeStep);
		~VertexBuffer();

		void add(const Vertex& vertex);
		void remove(unsigned int location);
		void remove(const Vertex& vertex);
		void replace(unsigned int location, const Vertex& newVertex);
		void replace(const Vertex& oldVertex, const Vertex& newVertex);

		bool isEmpty() const;
		bool contains(const Vertex& vertex);

		unsigned int getCount() const;
		int find(const Vertex& vertex);

		void clear();

	private:
		unsigned int vertexCounter;
		unsigned int bufferLength;
		unsigned int resizeStep;

		Vertex* data;

		void resize();
		bool needToResize();
	};

}