#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/vec3.hpp>
#include <array>
#include <map>

enum Options {
	Option_Invalid,
	v,
	vn,
	f
};

inline Options resolveOption(std::string input);

struct Vertex
{
	float pos[3];
	float normal[3];
	float text[2]{ 0.0f,0.0f };

	inline bool operator==(Vertex v);
};

class objLoader
{
private:
	const std::string path;
	std::vector<float>position;
	std::vector<float>normal;

	std::vector<Vertex> vertex;
	size_t m_nIndex;
	std::vector<unsigned int>index;

	void lineLexer(std::string s);

public:
	objLoader() {};
	objLoader(std::string p);
	~objLoader() {};

	void read();

	inline unsigned int vertexSize() {
		return sizeof(Vertex);
	}

	inline size_t vertexArraySize() {
		return vertex.size() * sizeof(Vertex);
	}

	inline size_t indexArrayCount() {
		return index.size();
	}

	inline const void* vertexArrayPointer() {
		return &vertex[0];
	}

	inline const unsigned int* indexArrayPointer() {
		return &index[0];
	}

};
