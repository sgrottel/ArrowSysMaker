// ArrowSysMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Common.h"
#include "Vertex.h"
#include "PLYWriter.h"

void makeArrow(std::vector<Vertex>& ver, std::vector<glm::uvec3>& tri);
void merge(
	std::vector<Vertex>& ver, std::vector<glm::uvec3>& tri,
	std::vector<Vertex>& aver, std::vector<glm::uvec3>& atri);

int main()
{
	try
	{
		std::vector<Vertex> ver; // verticies
		std::vector<glm::uvec3> tri; // triangles

		std::vector<Vertex> aver; // verticies
		std::vector<glm::uvec3> atri; // triangles
		makeArrow(aver, atri);

		for (auto& v : aver) {
			v.c = glm::u8vec3{ 255, 0, 0 };
		}

		merge(ver, tri, aver, atri);

		for (auto& v : aver) {
			v.v = glm::vec3{ v.v.y, v.v.x, -v.v.z };
			v.n = glm::vec3{ v.n.y, v.n.x, -v.n.z };
			v.c = glm::u8vec3{ 0, 255, 0 };
		}

		merge(ver, tri, aver, atri);

		for (auto& v : aver) {
			v.v = glm::vec3{ -v.v.x, v.v.z, v.v.y };
			v.n = glm::vec3{ -v.n.x, v.n.z, v.n.y };
			v.c = glm::u8vec3{ 0, 0, 255 };
		}

		merge(ver, tri, aver, atri);

		writePLY("C:\\Downloads\\arrowsys.ply", ver, tri);
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "EXCEPTION: Unknown" << std::endl;
	}
}

void makeArrow(std::vector<Vertex>& ver, std::vector<glm::uvec3>& tri)
{
	glm::u8vec3 c{ 192, 192, 192 };
	glm::vec2 r[]{
		{1,0}, {sin45, sin45},
		{0,1}, {-sin45, sin45},
		{-1,0}, {-sin45, -sin45},
		{0,-1}, {sin45, -sin45}
	};
	double g[]{
		1, sin45,
		1, sin45,
		1, sin45,
		1, sin45
	};

	ver.clear();
	tri.clear();

	ver.push_back({ {-6, 0, 0}, {-1, 0, 0}, c }); //  0

	for (int i = 0; i < 8; ++i)
		ver.push_back({ {-6, r[i]}, {-1, 0, 0}, c }); //  1-8
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {-6, r[i]}, {0, r[i]}, c }); //  9-16
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {-g[i], r[i]}, {0, r[i]}, c }); //  17-24
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {g[i], r[i]}, {0, r[i]}, c }); //  25-32
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {6, r[i]}, {0, r[i]}, c }); //  33-40
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {6, r[i]}, {-1, 0, 0}, c }); //  41-48
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {6, r[i] * glm::vec2{2}}, {-1, 0, 0}, c }); //  49-56

	for (int i = 0; i < 8; ++i)
		ver.push_back({ {6, r[i] * glm::vec2{2}}, {0.5, r[i]}, c }); //  57-64
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {8, r[i]}, {0.5, r[i]}, c }); //  65-72
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {9, r[i] * glm::vec2{0.5}}, {0.5, r[i]}, c }); //  73-80
	for (int i = 0; i < 8; ++i)
		ver.push_back({ {9.8, r[i] * glm::vec2{0.1}}, {0.5, r[i]}, c }); //  81-88

	ver.push_back({ {10, 0, 0}, {1, 0, 0}, c }); //  89

	for (int i = 0; i < 8; ++i)
		tri.push_back({ (1 + i), 0, 1 + ((1 + i) % 8) });

	for (int k = 0; k < 3; ++k)
	{
		int a = 9 + k * 16;
		int b = 9 + 8 + k * 16;
		for (int i = 0; i < 8; ++i)
		{
			int j = (i + 1) % 8;
			tri.push_back({ a + i, a + j, b + i });
			tri.push_back({ a + j, b + j, b + i });
		}
	}

	for (int k = 0; k < 3; ++k)
	{
		int a = 57 + k * 8;
		int b = 57 + 8 + k * 8;
		for (int i = 0; i < 8; ++i)
		{
			int j = (i + 1) % 8;
			tri.push_back({ a + i, a + j, b + i });
			tri.push_back({ a + j, b + j, b + i });
		}
	}

	for (int i = 0; i < 8; ++i)
		tri.push_back({ 89, 81 + i, 81 + ((1 + i) % 8) });

	for (auto &v : ver) {
		v.n = glm::normalize(v.n);
	}
}

void merge(
	std::vector<Vertex>& ver, std::vector<glm::uvec3>& tri,
	std::vector<Vertex>& aver, std::vector<glm::uvec3>& atri)
{
	size_t to = ver.size();
	ver.insert(ver.end(), aver.begin(), aver.end());
	for (glm::uvec3 const& t : atri)
		tri.push_back(t + glm::uvec3{ to });
}
