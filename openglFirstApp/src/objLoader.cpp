#include "objLoader.h"

inline bool Vertex::operator==(Vertex v) {
	if (v.pos[0] == pos[0] && v.pos[1] == pos[1] && v.pos[2] == pos[2] &&
		v.normal[0] == normal[0] && v.normal[1] == normal[1] && v.normal[2] == normal[2] &&
		v.text[0] == text[0] && v.text[1] == text[1]) {
		return true;
	}
	else {
		return false;
	}
}

inline Options resolveOption(std::string input) {
	if (input == "v")	return v;
	else if (input == "vn") return vn;
	else if (input == "f")	return f;
	//...
	return Option_Invalid;
};

objLoader::objLoader(std::string p) : path(p) {
	std::ifstream in(path);
	std::string line;
	std::getline(in, line);
	size_t pos1 = 0;
	while (!in.eof())
	{
		pos1 = line.find(' ');
		switch (resolveOption(line.substr(0, pos1)))
		{
		case(v):
			//first vertex
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			position.push_back(std::stof(line));
			//second vertex
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			position.push_back(std::stof(line));
			//third vertex
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			position.push_back(std::stof(line));
			break;

		case(vn):
			//first vertex normal
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			normal.push_back(std::stof(line));
			//second vertex normal
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			normal.push_back(std::stof(line));
			//third vertex normal
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			normal.push_back(std::stof(line));
			break;

		case(f):
			//first index of a face
			pos1 = line.find(' ');
			line = line.substr(pos1 + 1);
			lineLexer(line + ' ');
			break;

		default:
			//std::cout << line << std::endl;
			break;
		}
		std::getline(in, line);
	}
	in.close();

//#define DEBUG //Print Vertex
#ifdef DEBUG
	for (size_t i = 0; i < vertex.size(); i = i + 3)
	{
		std::cout << "1:" << vertex[i] << "\t" << " 2:" << vertex[i + 1] << "\t" << " 3:" << vertex[i + 2] << "\t" << std::endl;
	}
	for (size_t i = 0; i < index.size(); i = i + 3)
	{
		std::cout << "1:" << index[i] << "\t" << " 2:" << index[i + 1] << "\t" << " 3:" << index[i + 2] << "\t" << std::endl;
	}
#endif // DEBUG
}
