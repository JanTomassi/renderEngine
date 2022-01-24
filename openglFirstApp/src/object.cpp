#include "object.h"

object::c_object::c_object(){}

object::c_object::c_object(std::string p) : obj(objLoader(p)) {
	
	va.Bind();
	vb.SetData(obj.vertexArrayPointer(), obj.vertexArraySize());

	BufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	ib.SetData(obj.indexArrayPointer(), obj.indexArrayCount());
}

object::c_object::~c_object()
{
	//delete va;
	//delete vb;
	//delete ib;
}

void object::c_object::Activate() {
	va.Bind();
	vb.Bind();
	ib.Bind();
}

void object::c_object::Disactivate() {
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
}

void object::c_object::render() {
	va.Bind(); vb.Bind(); ib.Bind();
	GLCALL(glDrawElements(GL_TRIANGLES, obj.indexArrayCount(), GL_UNSIGNED_INT, nullptr));
}
