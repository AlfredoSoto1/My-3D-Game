#include "vertexBuffer.h"
#include "../maths/vectors.h"

using namespace maths;
using namespace buffer;

//struct buffer::Vertex {
//	vec3 position;
//	vec3 normal;
//	unsigned int index;
//
//	bool operator == (const Vertex& vertex) {
//		bool samePosition = position == vertex.position;
//		bool sameNormal = normal == vertex.normal;
//		return samePosition && sameNormal;
//	}
//};

VertexBuffer::VertexBuffer(unsigned int resizeStep) 
	: bufferLength(resizeStep), vertexCounter(0), resizeStep(resizeStep)
{
	resize();
}

VertexBuffer::~VertexBuffer() {
	clear();
}

void VertexBuffer::resize() {
	if (data == nullptr) {
		data = new Vertex[bufferLength];
		return;
	}
	Vertex* tempData = new Vertex[bufferLength * 2];
	for (unsigned int i = 0; i < bufferLength; i++)
		tempData[i] = data[i];
	delete[] data;
	data = tempData;
	bufferLength *= 2;
}

bool VertexBuffer::needToResize() {
	return bufferLength == vertexCounter;
}

void VertexBuffer::add(const Vertex& vertex) {
	if (needToResize())
		resize();
	//add vertex to list
	data[vertexCounter++] = vertex;
	//add vertex to list after verifying that its unique
}

void VertexBuffer::remove(unsigned int location) {
	for (int i = location; i < vertexCounter - 1; i++)
		data[i] = data[i + 1];
	vertexCounter--;
}

void VertexBuffer::remove(const Vertex& vertex) {
	int location = find(vertex);
	if (location != -1)
		remove((unsigned int)location);
}

void VertexBuffer::replace(unsigned int location, const Vertex& newVertex) {
	data[location] = newVertex;
}

void VertexBuffer::replace(const Vertex& oldVertex, const Vertex& newVertex) {
	int location = find(oldVertex);
	if (location != -1)
		data[location] = newVertex;
}

Vertex* VertexBuffer::get(unsigned int location) {
	return &data[location];
}

bool VertexBuffer::isEmpty() const {
	return vertexCounter == 0;
}

bool VertexBuffer::contains(const Vertex& vertex) {
	if (find(vertex) != -1)
		return true;
	else
		return false;
}

unsigned int VertexBuffer::getCount() const {
	return vertexCounter;
}

int VertexBuffer::find(const Vertex& vertex) {
	for (unsigned int i = 0; i < vertexCounter; i++) {
		Vertex& iteratingVertex = data[i];
		if (iteratingVertex == vertex)
			return i;
	}
	return -1;
}

void VertexBuffer::clear() {
	vertexCounter = 0;
	bufferLength = resizeStep;
	if (data != nullptr)
		delete[] data;
	data = nullptr;
}