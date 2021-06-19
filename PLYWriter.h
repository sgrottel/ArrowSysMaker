#pragma once

#include <vector>
#include "Common.h"

void writePLY(const char* filename, const std::vector<Vertex>& v, const std::vector<glm::uvec3>& t);
