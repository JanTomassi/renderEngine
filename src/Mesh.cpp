#include "Mesh.h"

object::Mesh::Mesh (std::string p) { obj = new objLoader (p); }

void
object::Mesh::loadMesh ()
{
  obj->read ();
  face_number = obj->indexArrayCount ();
}

// Allocate the buffer array set the data
void
object::Mesh::Allocate ()
{
  Activate ();
  vb.SetData (GL_ARRAY_BUFFER, obj->vertexArrayPointer (),
              obj->vertexArraySize ());

  BufferLayout layout;
  layout.Push<float> (3);
  layout.Push<float> (3);
  layout.Push<float> (2);
  va.AddBuffer (vb, layout);

  ib.SetData (obj->indexArrayPointer (), face_number);
  delete obj;
  Disactivate ();
}

object::Mesh::~Mesh () {}

void
object::Mesh::Activate ()
{
  va.Bind ();
  vb.Bind ();
  ib.Bind ();
}

void
object::Mesh::Disactivate ()
{
  va.Unbind ();
  vb.Unbind ();
  ib.Unbind ();
}

void
object::Mesh::render ()
{
  va.Bind ();
  GLCALL (
      glDrawElements (GL_TRIANGLES, face_number, GL_UNSIGNED_INT, nullptr));
}
