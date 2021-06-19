#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 v; // position
	glm::vec3 n; // normal
	glm::u8vec3 c; // color
};
