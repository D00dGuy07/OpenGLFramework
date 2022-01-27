#pragma once

#include "glm/glm.hpp"

#include "glad/glad.h"

// Texture Atlas

struct TextureCoords
{
	glm::vec2 v0;
	glm::vec2 v1;
	glm::vec2 v2;
	glm::vec2 v3;
};

// (x, y) of (0, 0) gives bottom left corner. Width and Height are of the individual sprites
TextureCoords TextureAtlasCoords(float x, float y, float width, float height);


// Used to set up opengl memory barriers
class GLMemoryHelper
{
public:
	enum class BarrierType : uint32_t
	{
		VertAttribArray = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, 
		ElementArray = GL_ELEMENT_ARRAY_BARRIER_BIT, 
		Uniform = GL_UNIFORM_BARRIER_BIT, 
		TexFetch = GL_TEXTURE_FETCH_BARRIER_BIT, 
		ShaderImgAccess = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, 
		Command = GL_COMMAND_BARRIER_BIT, 
		PixBuf = GL_PIXEL_BUFFER_BARRIER_BIT, 
		TexUpdate = GL_TEXTURE_UPDATE_BARRIER_BIT, 
		BufUpdate = GL_BUFFER_UPDATE_BARRIER_BIT, 
		Framebuffer = GL_FRAMEBUFFER_BARRIER_BIT, 
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BARRIER_BIT, 
		AtomicCounter = GL_ATOMIC_COUNTER_BARRIER_BIT, 
		ShaderStorage = GL_SHADER_STORAGE_BARRIER_BIT,
		All = GL_ALL_BARRIER_BITS
	};

	static void Barrier(BarrierType type);
};

// For bit masking
GLMemoryHelper::BarrierType inline operator||(const GLMemoryHelper::BarrierType& first, const GLMemoryHelper::BarrierType& second);