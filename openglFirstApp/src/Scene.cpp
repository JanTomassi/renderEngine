#include "Scene.h"

void Scene::loadSynch(std::string filepath)
{
	auto m = new object::Mesh(filepath);
	meshs.push_back(m);
}

void Scene::render()
{
	for (auto& mesh : meshs)
	{
		mesh->render();
	}
}
