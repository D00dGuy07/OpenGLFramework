#include "Renderer/Helpers.h"

#include "Renderer/Renderer.h"

// Texture Atlas

TextureCoords TextureAtlasCoords(float x, float y, float width, float height)
{
	return {
		glm::vec2(((x * width))        , ((y * width) + width)),
		glm::vec2(((x * width) + width), ((y * width) + width)),
		glm::vec2(((x * width) + width), (y * width)),
		glm::vec2(((x * width))        , (y * width))
	};
}

// Memory Helper

void GLMemoryHelper::Barrier(GLMemoryHelper::BarrierType type)
{
	Renderer::Submit([=]() {
		glMemoryBarrier(static_cast<uint32_t>(type));
	});
}

GLMemoryHelper::BarrierType operator||(const GLMemoryHelper::BarrierType& first, const GLMemoryHelper::BarrierType& second)
{ 
	return static_cast<GLMemoryHelper::BarrierType>(static_cast<uint32_t>(first) || static_cast<uint32_t>(second)); 
}