#include "Mesh.h"

object::Mesh::Mesh(std::string p) {
	obj = new objLoader(p);
}

void object::Mesh::loadMesh()
{
	obj->read();
}

void object::Mesh::Allocate()
{
	va.Bind();
	vb.SetData(obj->vertexArrayPointer(), obj->vertexArraySize());

	BufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	ib.SetData(obj->indexArrayPointer(), obj->indexArrayCount());
}

object::Mesh::~Mesh()
{
	delete obj;
}

void object::Mesh::Activate() {
	va.Bind();
	vb.Bind();
	ib.Bind();
}

void object::Mesh::Disactivate() {
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
}

void object::Mesh::render() {
	va.Bind(); vb.Bind(); ib.Bind();
	GLCALL(glDrawElements(GL_TRIANGLES, obj->indexArrayCount(), GL_UNSIGNED_INT, nullptr));
}
