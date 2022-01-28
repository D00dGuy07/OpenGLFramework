#include "Texture.h"

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "Renderer/Renderer.h"

uint32_t Texture::m_BoundRendererID = 0xFFFFFFFF;

Texture::Texture(const std::string& path, int32_t magFilter)
	: ImageBuffer(NULL, 0, 0), m_LocalBuffer(nullptr), m_BPP(0), m_Format(InternalImageFormat::RGBA8)
{
	Renderer::Submit([&, path, magFilter]() {
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	});
}

Texture::Texture(int32_t width, int32_t height, InternalImageFormat format)
	: ImageBuffer(NULL, width, height), m_BPP(32), m_Format(format), m_LocalBuffer(NULL)
{
	int32_t sizedId = 0, baseId = 0;
	ImageBuffer::GetFormatData(m_Format, sizedId, baseId);
	Renderer::Submit([&, sizedId, baseId]() {
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, sizedId, m_Width, m_Height, 0, baseId, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	});
}

Texture::~Texture()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteTextures(1, &id);
	});
}

void Texture::Bind(uint32_t slot) const
{
	Renderer::Submit([=]() {
		if (m_BoundRendererID == m_RendererID)
			return;
		m_BoundRendererID = m_RendererID;
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	});
}

void Texture::BindImage(uint32_t slot)
{
	int32_t sizedId = 0, baseId = 0;
	ImageBuffer::GetFormatData(m_Format, sizedId, baseId);
	Renderer::Submit([=]() {
		glBindImageTexture(slot, m_RendererID, 0, GL_FALSE, 0, GL_READ_WRITE, sizedId);
	});
}

void Texture::Reallocate(int32_t width, int32_t height)
{
	m_Width = width;
	m_Height = height;

	int32_t sizedId = 0, baseId = 0;
	ImageBuffer::GetFormatData(m_Format, sizedId, baseId);

	Bind();
	Renderer::Submit([=]() {
		glTexImage2D(GL_TEXTURE_2D, 0, sizedId, m_Width, m_Height, 0, baseId, GL_UNSIGNED_BYTE, NULL);
	});
}