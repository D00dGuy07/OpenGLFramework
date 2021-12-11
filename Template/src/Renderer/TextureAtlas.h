#pragma once

#include "glm/glm.hpp"

struct TextureCoords
{
	glm::vec2 v0;
	glm::vec2 v1;
	glm::vec2 v2;
	glm::vec2 v3;
};

// (x, y) of (0, 0) gives bottom left corner. Width and Height are of the individual sprites
TextureCoords GetTextureCoords(float x, float y, float width, float height);