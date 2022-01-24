#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/vec3.hpp>
#include <iostream>
#include <array>
#include "objLoader.h"
#include "Application.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"

namespace object {
	static class c_object
	{
	private:
		unsigned int m_RenderId;

		objLoader obj;
		glclass::VertexArray va;
		glclass::Buffer vb;
		glclass::IndexBuffer ib;

	public:
		c_object();
		c_object(std::string p);
		~c_object();

		void render();
		void Activate();
		void Disactivate();
	};
}

