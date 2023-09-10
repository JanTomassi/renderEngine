#pragma once
#include "Mesh.h"
#include <vector>
#include <mutex>


class Scene
{
private:
	std::vector<object::Mesh*> meshs;
	std::vector<object::Mesh*> toLoads;
	std::mutex sceneLockMesh;
public:
	Scene(GLFWwindow* main) {
		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	};
	~Scene() {};
	void loadSynch(object::Mesh* m);

	void loadsAsync(std::vector<std::string> filepaths);

	void addToLoadList(object::Mesh* m);
	void addMeshs();
	void render();

	inline object::Mesh* operator[](size_t i) {
		return meshs[i];
	}
};

