#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <iostream>

uint32_t VertexArray::m_BoundRendererID = 0xFFFFFFFF;

VertexArray::VertexArray()
	: m_RendererID(NULL)
{
	Renderer::Submit([&]() {
		glGenVertexArrays(1, &m_RendererID);
	});
	
}

VertexArray::~VertexArray()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteVertexArrays(1, &id);
	});
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		unsigned int stride = layout.GetStride();
		Renderer::Submit([=]() {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type,
				element.normalized, stride, (const void*)offset);
		});
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	Renderer::Submit([=]() {
		if (m_BoundRendererID == m_RendererID)
			return;
		m_BoundRendererID = m_RendererID;
		glBindVertexArray(m_RendererID);
	});
}