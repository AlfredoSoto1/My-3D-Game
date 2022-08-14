#include "chunkBuilder.h"

#include "maths/functions.h"
#include "tables.h"

#include <iostream>

using namespace generation;

struct ChunkBuilder::Vertex {
	maths::vec3 position;
	maths::vec3 normal;
};

struct ChunkBuilder::Voxel {
	int x, y, z;
	int step;
	float data[8] = {
		0.0, 0.0, 0.0, 0.0,
		1.0, 1.0, 1.0, 1.0
	};
};

ChunkBuilder::ChunkBuilder() {
	vertices = new structs::ArrayList<Vertex>(1000);
	indices  = new structs::ArrayList<unsigned int>(1000);
}

ChunkBuilder::~ChunkBuilder() {
	delete vertices;
	delete indices;

	delete[] modelCoords;
	delete[] modelNormals;
	delete[] modelIndices;
}

void ChunkBuilder::buildExample() {

	//getVoxel(0, 0, 0, 1, maths::vec3(0.0), 16, nullptr, &voxel);

	float density[16][16][16];
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				density[x][y][z] = sin(maths::toDegree((float)x)) + cos(maths::toDegree((float)z)) + sin(maths::toDegree((float)y));
				//density[x][y][z] = -y + 4.0;
			}
		}
	}


	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			for (int z = 0; z < 8; z++) {
				Voxel voxel;

				voxel.x = x;
				voxel.y = y;
				voxel.z = z;

				voxel.step = 1;

				voxel.data[0] = density[x][y][z];
				voxel.data[1] = density[x][y][z+1];
				voxel.data[2] = density[x+1][y][z+1];
				voxel.data[3] = density[x+1][y][z];

				voxel.data[4] = density[x][y+1][z];
				voxel.data[5] = density[x][y+1][z+1];
				voxel.data[6] = density[x+1][y+1][z+1];
				voxel.data[7] = density[x+1][y+1][z];

				buildVertices(voxel);
			}
		}
	}

	toMesh();

	std::cout << "Total vertices: " << modelCoordListLength << std::endl;
	std::cout << "Total indices: " << modelIndexListLength << std::endl;
}

void ChunkBuilder::getVoxel(int x, int y, int z, int step, const maths::vec3& chunkPosition, int chunkLength, float* density, Voxel* voxel) {
	int chunkLengthEx = chunkLength + 1;

	int xp = (int)(x + chunkPosition.x);
	int yp = (int)(y + chunkPosition.y);
	int zp = (int)(z + chunkPosition.z);

	int x0y0z0 = ( xp +         yp * chunkLengthEx +  zp         * chunkLengthEx * chunkLengthEx);
	int x0y0z1 = ( xp +         yp * chunkLengthEx + (zp + step) * chunkLengthEx * chunkLengthEx);
	int x1y0z1 = ((xp + step) + yp * chunkLengthEx + (zp + step) * chunkLengthEx * chunkLengthEx);
	int x1y0z0 = ((xp + step) + yp * chunkLengthEx +  zp         * chunkLengthEx * chunkLengthEx);

	int x0y1z0 = ( xp +         (yp + step) * chunkLengthEx +  zp         * chunkLengthEx * chunkLengthEx);
	int x0y1z1 = ( xp +         (yp + step) * chunkLengthEx + (zp + step) * chunkLengthEx * chunkLengthEx);
	int x1y1z1 = ((xp + step) + (yp + step) * chunkLengthEx + (zp + step) * chunkLengthEx * chunkLengthEx);
	int x1y1z0 = ((xp + step) + (yp + step) * chunkLengthEx +  zp         * chunkLengthEx * chunkLengthEx);

	voxel->data[0] = density[x0y0z0];
	voxel->data[1] = density[x0y0z1];
	voxel->data[2] = density[x1y0z1];
	voxel->data[3] = density[x1y0z0];

	voxel->data[4] = density[x0y1z0];
	voxel->data[5] = density[x0y1z1];
	voxel->data[6] = density[x1y1z1];
	voxel->data[7] = density[x1y1z0];
}

void ChunkBuilder::buildVertices(const Voxel& voxel) {
	int* edgeConfig = getIndexEdgeConfig(surfaceLevel, voxel);

	for (int i = 0; edgeConfig[i] != -1; i += 3) {

		int a0 = cornerIndexAFromEdge[edgeConfig[i]];
		int b0 = cornerIndexBFromEdge[edgeConfig[i]];

		int a1 = cornerIndexAFromEdge[edgeConfig[i + 1]];
		int b1 = cornerIndexBFromEdge[edgeConfig[i + 1]];

		int a2 = cornerIndexAFromEdge[edgeConfig[i + 2]];
		int b2 = cornerIndexBFromEdge[edgeConfig[i + 2]];

		float interpolationLevel1 = interpolation ? maths::interpolate(surfaceLevel, voxel.data[b0], voxel.data[a0]) : 0.5f;
		float interpolationLevel2 = interpolation ? maths::interpolate(surfaceLevel, voxel.data[b1], voxel.data[a1]) : 0.5f;
		float interpolationLevel3 = interpolation ? maths::interpolate(surfaceLevel, voxel.data[b2], voxel.data[a2]) : 0.5f;

		Vertex vert1;
		Vertex vert2;
		Vertex vert3;

		vert1.position = getTrianglePoint(a0, b0, interpolationLevel1, voxel);
		vert2.position = getTrianglePoint(a1, b1, interpolationLevel2, voxel);
		vert3.position = getTrianglePoint(a2, b2, interpolationLevel3, voxel);

		maths::vec3 normal = maths::getNormal(vert1.position, vert2.position, vert3.position);

		vert1.normal = normal;
		vert2.normal = normal;
		vert3.normal = normal;

		pushVertex(vert1);
		pushVertex(vert2);
		pushVertex(vert3);
	}
}

maths::vec3 ChunkBuilder::getTrianglePoint(int a, int b, float interpolation, const Voxel& voxel) {
	float vx = maths::distInterpolation(voxelBox[a][0], voxelBox[b][0], interpolation) * voxel.step + voxel.x;
	float vy = maths::distInterpolation(voxelBox[a][1], voxelBox[b][1], interpolation) * voxel.step + voxel.y;
	float vz = maths::distInterpolation(voxelBox[a][2], voxelBox[b][2], interpolation) * voxel.step + voxel.z;
	return maths::vec3(vx, vy, vz);
}

int* ChunkBuilder::getIndexEdgeConfig(double surfaceLevel, const Voxel& voxel) {
	int cubeIndex = 0;
	for (int i = 0; i < 8; i++)
		if (voxel.data[i] <= surfaceLevel)
			cubeIndex |= 1 << i;
	return triangleEdgeConfiguration[cubeIndex];
}

void ChunkBuilder::pushVertex(const Vertex& vertex) {
	if (!shareVertices) {
		vertices->add(vertex);
		indices->add(indexCounter++);
		return;
	}
	if (!vertices->contains(vertex)) {
		//push vertex to list
		vertices->add(vertex);
		indices->add(indexCounter++);
	}
	else {
		int i = vertices->indexOf(vertex);
		indices->add(i);
		//combine normals when sharing vertex
		Vertex& vertexFromArray = *vertices->get(i);
		maths::vec3 combinedNormal = vertexFromArray.normal + vertex.normal;
		vertexFromArray.normal = combinedNormal;

		std::cout << "sharing " << i << std::endl;
	}
}

void ChunkBuilder::toMesh() {
	modelCoords = new float[vertices->getCount() * 3];
	modelNormals = new float[vertices->getCount() * 3];
	modelIndices = new unsigned int[indices->getCount()];

	modelCoordListLength = vertices->getCount() * 3;
	modelIndexListLength = indices->getCount();

	for (int i = 0; i < indices->getCount() / 3; i++) {
		int index0 = i * 3 + 0;
		int index1 = i * 3 + 1;
		int index2 = i * 3 + 2;
		//filter indices
		modelIndices[index0] = *indices->get(index0);
		modelIndices[index1] = *indices->get(index1);
		modelIndices[index2] = *indices->get(index2);

		//filter vertices
		Vertex& vertex0 = *vertices->get(modelIndices[index0]);
		Vertex& vertex1 = *vertices->get(modelIndices[index1]);
		Vertex& vertex2 = *vertices->get(modelIndices[index2]);

		//filter positions
		modelCoords[modelIndices[index0] * 3 + 0] = vertex0.position.x;
		modelCoords[modelIndices[index0] * 3 + 1] = vertex0.position.y;
		modelCoords[modelIndices[index0] * 3 + 2] = vertex0.position.z;

		modelCoords[modelIndices[index1] * 3 + 0] = vertex1.position.x;
		modelCoords[modelIndices[index1] * 3 + 1] = vertex1.position.y;
		modelCoords[modelIndices[index1] * 3 + 2] = vertex1.position.z;

		modelCoords[modelIndices[index2] * 3 + 0] = vertex2.position.x;
		modelCoords[modelIndices[index2] * 3 + 1] = vertex2.position.y;
		modelCoords[modelIndices[index2] * 3 + 2] = vertex2.position.z;

		//filter normals
		modelNormals[modelIndices[index0] * 3 + 0] = vertex0.normal.x;
		modelNormals[modelIndices[index0] * 3 + 1] = vertex0.normal.y;
		modelNormals[modelIndices[index0] * 3 + 2] = vertex0.normal.z;

		modelNormals[modelIndices[index1] * 3 + 0] = vertex1.normal.x;
		modelNormals[modelIndices[index1] * 3 + 1] = vertex1.normal.y;
		modelNormals[modelIndices[index1] * 3 + 2] = vertex1.normal.z;

		modelNormals[modelIndices[index2] * 3 + 0] = vertex2.normal.x;
		modelNormals[modelIndices[index2] * 3 + 1] = vertex2.normal.y;
		modelNormals[modelIndices[index2] * 3 + 2] = vertex2.normal.z;
	}
}
