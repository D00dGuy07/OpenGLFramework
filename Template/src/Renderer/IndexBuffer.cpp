#include "IndexBuffer.h"

#include "Renderer.h"

uint32_t IndexBuffer::m_BoundRendererID = 0xFFFFFFFF;

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	: m_Count(count)
{
	// Not wrapped in submit because it uses a data buffer with an unknown memory lifespan
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteBuffers(1, &id);
	});
}

void IndexBuffer::Bind() const
{
	Renderer::Submit([=]() {
		if (m_BoundRendererID == m_RendererID)
			return;
		m_BoundRendererID = m_RendererID;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	});
}
