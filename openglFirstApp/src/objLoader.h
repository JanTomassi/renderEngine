#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/vec3.hpp>
#include <iostream>
#include <array>
#include <map>

static enum Options {
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
	size_t dic;
	std::vector<unsigned int>index;

	void lineLexer(std::string s) {
		while (s != "")
		{
			//auto s_p = s.find(' ');
			//auto key = s.substr(0, s_p);
			//dic.push_back(key);

			auto s_p = s.find('/');
			auto pos_i = std::stoi(s.substr(0, s_p)) - 1;
			s = s.substr(s_p + 1);

			s_p = s.find('/');
			auto text_i = std::stoi("0");//s.substr(0,s_p))-1;
			s = s.substr(s_p + 1);

			s_p = s.find(' ');
			auto normal_i = std::stoi(s.substr(0, s_p)) - 1;
			s = s.substr(s_p + 1);
			Vertex ver;
			ver.pos[0] = position[pos_i * 3];
			ver.pos[1] = position[(pos_i * 3) + 1];
			ver.pos[2] = position[(pos_i * 3) + 2];

			ver.normal[0] = normal[normal_i * 3];
			ver.normal[1] = normal[(normal_i * 3) + 1];
			ver.normal[2] = normal[(normal_i * 3) + 2];

			auto pos_vec = std::find(vertex.begin(), vertex.end(), ver);


			if (pos_vec != vertex.end()) {
				int idx = pos_vec - vertex.begin();
				index.push_back(idx);
			}
			else {
				vertex.push_back(ver);
				index.push_back(dic++);
			}
		}
	}

public:
	objLoader() {};
	objLoader(std::string p);
	~objLoader() {};

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