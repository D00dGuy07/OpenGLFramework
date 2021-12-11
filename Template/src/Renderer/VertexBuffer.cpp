#include "VertexBuffer.h"

#include "Renderer.h"
#include <iostream>

uint32_t VertexBuffer::m_BoundRendererID = 0xFFFFFFFF;

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	// Not wrapped in submit because it copies from a data buffer with an unknown memory lifespan
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteBuffers(1, &id);
	});
}

void VertexBuffer::Bind() const
{
	Renderer::Submit([=]() {
		if (m_BoundRendererID == m_RendererID)
			return;
		m_BoundRendererID = m_RendererID;
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	});
}