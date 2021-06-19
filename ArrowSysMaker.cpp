// ArrowSysMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Common.h"
#include "PLYWriter.h"

int main()
{
	try {
		std::vector<Vertex> ver; // verticies
		std::vector<glm::uvec3> tri; // triangles

		ver.push_back({ {1, 0, 0}, {1, 0, 0}, {255, 0, 0} });
		ver.push_back({ {0, 1, 0}, {0, 1, 0}, {0, 255, 0} });
		ver.push_back({ {0, 0, 1}, {0, 0, 1}, {0, 0, 255} });

		tri.push_back({ 0, 1, 2 });


		writePLY("C:\\Downloads\\arrowsys.ply", ver, tri);
	}
	catch (std::exception& e) {
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "EXCEPTION: Unknown" << std::endl;
	}
}
