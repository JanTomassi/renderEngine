#pragma once
#include "Mesh.h"
#include <vector>
class Scene
{
private:
	std::vector<object::Mesh*> meshs;
public:
	Scene() {};
	~Scene() {};
	void loadSynch(std::string filepath);
	void render();

	inline object::Mesh* operator[](size_t i) {
		return meshs[i];
	}
};

