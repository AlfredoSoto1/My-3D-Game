#include "mesh.h"

#include <GL/glew.h>
#include <iostream>

#include "../../structs/arrayList.h"

using namespace structs;
using namespace geometry;

/*
	Constructor
	+ This generates a VAO and stores its ID
	+ Also, it creates an ArrayList to store 
	+ all indices and vbos created
*/

Mesh::Mesh() {
	glGenVertexArrays(1, &vao);

	this->vboList = new ArrayList<unsigned int>(4);
	this->attribNumberList = new ArrayList<unsigned int>(4);
}

Mesh::~Mesh() {
	//deletes vao
	glDeleteVertexArrays(1, &vao);
	//delete ibo
	if (this->hasIbo)
		glDeleteBuffers(1, &ibo);

	ArrayList<unsigned int>* vboList = (ArrayList<unsigned int>*)this->vboList;
	ArrayList<unsigned int>* attribNumberList = (ArrayList<unsigned int>*)this->attribNumberList;

	//delete vbos
	for (int i = 0; i < vboList->getLength(); i++)
		glDeleteBuffers(1, vboList->get(i));
	//clears vbo list
	vboList->clear();
	attribNumberList->clear();

	delete vboList;
	delete attribNumberList;
}

unsigned int Mesh::getVao() const {
	return vao;
}

unsigned int Mesh::getIbo() const {
	return ibo;
}

unsigned int Mesh::getIndexCount() const {
	if (!hasIbo) {
		ArrayList<unsigned int>* vboList = (ArrayList<unsigned int>*)this->vboList;
		return (unsigned int)vboList->getLength();//wrong aqui se pone el vertex length
	}
	return indexCount;
}

void Mesh::bind() const {
	ArrayList<unsigned int>* attribNumberList = (ArrayList<unsigned int>*)this->attribNumberList;
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	for (int i = 0; i < attribNumberList->getLength(); i++)
		glEnableVertexAttribArray(*attribNumberList->get(i));
}

void Mesh::unbind() const {
	ArrayList<unsigned int>* attribNumberList = (ArrayList<unsigned int>*)this->attribNumberList;
	for (int i = 0; i < attribNumberList->getLength(); i++)
		glDisableVertexAttribArray(*attribNumberList->get(i));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::createIndexBuffer(int length, unsigned int* data) {
	if (hasIbo)
		return;
	//bind vao
	glBindVertexArray(vao);
	//create a ibo
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	this->ibo = ibo;
	this->indexCount = length;
	this->hasIbo = true;
	//store data to ibo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), data, GL_STATIC_DRAW);
	//unbind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//unbind vao
	glBindVertexArray(0);
}

void Mesh::createAttribute(unsigned int location, int dimension, int length, void* data, unsigned int type) {
	//bind vao
	glBindVertexArray(vao);
	//create a vbo
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//store vbo id
	ArrayList<unsigned int>* vboList = (ArrayList<unsigned int>*)this->vboList;
	vboList->add(vbo);
	//set size of _data
	int totalDataBytes = dimension * length * sizeof(float); //float is the default
	switch (type) {
	case GL_INT:
		totalDataBytes = dimension * length * sizeof(int);
		break;
	case GL_SHORT:
		totalDataBytes = dimension * length * sizeof(short);
		break;
	case GL_BYTE:
		totalDataBytes = dimension * length * sizeof(char);
		break;
	}
	glBufferData(GL_ARRAY_BUFFER, totalDataBytes, data, GL_STATIC_DRAW);
	glVertexAttribPointer(location, dimension, type, GL_FALSE, 0, 0);//fix stride in case of future error
	ArrayList<unsigned int>* attribNumberList = (ArrayList<unsigned int>*)this->attribNumberList;
	attribNumberList->add(location);
	//unbinds vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind vao
	glBindVertexArray(0);
}