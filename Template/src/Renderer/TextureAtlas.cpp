#include "TextureAtlas.h"

TextureCoords GetTextureCoords(float x, float y, float width, float height)
{
	return {
		glm::vec2(((x * width))        , ((y * width) + width)),
		glm::vec2(((x * width) + width), ((y * width) + width)),
		glm::vec2(((x * width) + width), (y * width)),
		glm::vec2(((x * width))        , (y * width))
	};
}