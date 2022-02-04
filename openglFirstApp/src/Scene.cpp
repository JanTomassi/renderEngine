#include "Scene.h"
#include <thread> 
#include <mutex>

void Scene::loadSynch(object::Mesh* m)
{
	m->loadMesh();
	std::lock_guard<std::mutex> lock(sceneLockMesh);
	toLoads.push_back(m);//add Mesh to loading queue 
}

void Scene::loadsAsync(std::vector<std::string> filepaths) {
	for (const auto& fp : filepaths)
	{
		object::Mesh* m = new object::Mesh(fp);
		std::thread loadmesh(&Scene::loadSynch, this, m);
		loadmesh.detach();
	}
}

// Call from render funcion to allocate and bind the new object
void Scene::addMeshs() {
	std::lock_guard<std::mutex> lock(sceneLockMesh);
	for (const auto& toLoad : toLoads)
	{
		toLoad->Allocate();
		meshs.push_back(toLoad);
	}
	toLoads.clear();
}

void Scene::render()
{
	if (toLoads.size()>0)
		addMeshs();

	for (auto& mesh : meshs)
	{
		mesh->render();
	}
}
