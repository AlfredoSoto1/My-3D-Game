#pragma once

#ifndef _CHUNK_BUILDER_DEFINED
#define _CHUNK_BUILDER_DEFINED

#include "maths/vectors.h"
#include "structs/arrayList.h"
#include "memory/vertexBuffer.h"

namespace generation {

	class ChunkBuilder {
	public:
		float* modelCoords;
		float* modelNormals;
		unsigned int* modelIndices;

		unsigned int modelCoordListLength = 0;
		unsigned int modelIndexListLength = 0;

		ChunkBuilder();
		~ChunkBuilder();

		void buildExample();

	private:
		double surfaceLevel = 0.1;

		bool interpolation = true;
		bool shareVertices = false;

		struct Vertex;
		struct Voxel;

		buffer::VertexBuffer* vertexBuffer;

		structs::ArrayList<Vertex>* vertices;
		structs::ArrayList<unsigned int>* indices;

		unsigned int indexCounter = 0;

		void getVoxel(int x, int y, int z, int step, const maths::vec3& chunkPosition, int chunkLength, float* density, Voxel* voxel);

		void buildVertices(const Voxel& voxel);

		int* getIndexEdgeConfig(double surface, const Voxel& voxel);

		maths::vec3 getTrianglePoint(int a, int b, float interpolation, const Voxel& voxel);

		void pushVertex(const Vertex& vertex);

		void toMesh();
	};
}
#endif // !_CHUNK_BUILDER_DEFINED
