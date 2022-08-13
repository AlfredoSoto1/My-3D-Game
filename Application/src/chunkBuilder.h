#pragma once

#include "maths/functions.h"
#include "maths/vectors.h"

#include "structs/arrayList.h"

#include "tables.h"

namespace generation {

	class ChunkBuilder {
	public:
		ChunkBuilder();
		~ChunkBuilder();

	private:

	};
}


class ChunkBuilderOLD {
public:
	ArrayList<maths::vec3>* points;
	ArrayList<unsigned int>* indices;

	float* modelPoints;
	unsigned int* modelIndices;

	unsigned int totalIndexArrayLength = 0;
	unsigned int totalPointArrayLength = 0;

	ChunkBuilderOLD() {
		points = new ArrayList<maths::vec3>(1000);
		indices = new ArrayList<unsigned int>(1000);

		//temp
		create();

	}

	~ChunkBuilderOLD() {
		delete points;
		delete indices;

		delete[] modelPoints;
		delete[] modelIndices;
	}

private:
	unsigned int indexCounter = 0;
	bool interpolation = false;

	double surfaceLevel = 0.1;

	void toMesh() {
		modelPoints = new float[points->getCount() * 3];
		modelIndices = new unsigned int[indices->getCount()];

		totalIndexArrayLength = indices->getCount();
		totalPointArrayLength = points->getCount() * 3;

		for (int i = 0; i < indices->getCount() / 3; i++) {
			int index0 = i * 3 + 0;
			int index1 = i * 3 + 1;
			int index2 = i * 3 + 2;
			//filter indices
			modelIndices[index0] = *indices->get(index0);
			modelIndices[index1] = *indices->get(index1);
			modelIndices[index2] = *indices->get(index2);

			//filter vertices
			maths::vec3& point0 = *points->get(modelIndices[index0]);
			maths::vec3& point1 = *points->get(modelIndices[index1]);
			maths::vec3& point2 = *points->get(modelIndices[index2]);

			modelPoints[modelIndices[index0] * 3 + 0] = point0.x;
			modelPoints[modelIndices[index0] * 3 + 1] = point0.y;
			modelPoints[modelIndices[index0] * 3 + 2] = point0.z;

			modelPoints[modelIndices[index1] * 3 + 0] = point1.x;
			modelPoints[modelIndices[index1] * 3 + 1] = point1.y;
			modelPoints[modelIndices[index1] * 3 + 2] = point1.z;

			modelPoints[modelIndices[index2] * 3 + 0] = point2.x;
			modelPoints[modelIndices[index2] * 3 + 1] = point2.y;
			modelPoints[modelIndices[index2] * 3 + 2] = point2.z;

			////filter normals
			//Vector3f normal0 = normals.get(indexElements[index0]);
			//Vector3f normal1 = normals.get(indexElements[index1]);
			//Vector3f normal2 = normals.get(indexElements[index2]);

			//normalElements[indexElements[index0] * 3 + 0] = normal0.x;
			//normalElements[indexElements[index0] * 3 + 1] = normal0.y;
			//normalElements[indexElements[index0] * 3 + 2] = normal0.z;

			//normalElements[indexElements[index1] * 3 + 0] = normal1.x;
			//normalElements[indexElements[index1] * 3 + 1] = normal1.y;
			//normalElements[indexElements[index1] * 3 + 2] = normal1.z;

			//normalElements[indexElements[index2] * 3 + 0] = normal2.x;
			//normalElements[indexElements[index2] * 3 + 1] = normal2.y;
			//normalElements[indexElements[index2] * 3 + 2] = normal2.z;
		}
	}
	//void getVoxel(void* voxel, int x, int y, int z);

	void create() {

		float voxel1[8] = {
			1.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 0.0
		};

		calcVoxelPoints(voxel1, 0, 0, 0, 1);

		toMesh();
	}

	void calcVoxelPoints(float* voxel, int x, int y, int z, int scale) {
		int* edgeConfig = getEdgeConfiguration(surfaceLevel, voxel);

		for (int i = 0; edgeConfig[i] != -1; i += 3) {

			int a0 = cornerIndexAFromEdge[edgeConfig[i]];
			int b0 = cornerIndexBFromEdge[edgeConfig[i]];

			int a1 = cornerIndexAFromEdge[edgeConfig[i + 1]];
			int b1 = cornerIndexBFromEdge[edgeConfig[i + 1]];

			int a2 = cornerIndexAFromEdge[edgeConfig[i + 2]];
			int b2 = cornerIndexBFromEdge[edgeConfig[i + 2]];

			float avrg1 = interpolation ? maths::interpolate(surfaceLevel, voxel[b0], voxel[a0]) : 0.5f;
			float avrg2 = interpolation ? maths::interpolate(surfaceLevel, voxel[b1], voxel[a1]) : 0.5f;
			float avrg3 = interpolation ? maths::interpolate(surfaceLevel, voxel[b2], voxel[a2]) : 0.5f;

			maths::vec3 point1 = getTrianglePoint(a0, b0, avrg1, x, y, z, scale);
			maths::vec3 point2 = getTrianglePoint(a1, b1, avrg2, x, y, z, scale);
			maths::vec3 point3 = getTrianglePoint(a2, b2, avrg3, x, y, z, scale);

			maths::vec3 normal = maths::getNormal(point1, point2, point3);

			//add points to list
			points->add(point1);
			indices->add(indexCounter++);
			points->add(point2);
			indices->add(indexCounter++);
			points->add(point3);
			indices->add(indexCounter++);
		}
	}

	maths::vec3 getTrianglePoint(int a, int b, float avrg, int x, int y, int z, float step) {
		float vx = maths::distInterpolation(CORNERS[a][0], CORNERS[b][0], avrg) * step + x;
		float vy = maths::distInterpolation(CORNERS[a][1], CORNERS[b][1], avrg) * step + y;
		float vz = maths::distInterpolation(CORNERS[a][2], CORNERS[b][2], avrg) * step + z;
		return maths::vec3(vx, vy, vz);
	}

	int* getEdgeConfiguration(float surface, float* voxel) {
		int cubeIndex = 0;
		for (int i = 0; i < 8; i++)
			if (voxel[i] <= surface)
				cubeIndex |= 1 << i;
		return triangleEdgeConfiguration[cubeIndex];
	}
};