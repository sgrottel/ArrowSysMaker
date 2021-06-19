#pragma once

#include <glm/glm.hpp>

constexpr double sqrt2 = 1.41421356237309504880168872420969807856967187537694807317667973799;
constexpr double sin45 = 1.0 / sqrt2;

struct Vertex {
	glm::vec3 v; // position
	glm::vec3 n; // normal
	glm::u8vec3 c; // color
};
