#include "Mesh.h"

#include <iterator>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

Mesh::~Mesh()
{
	if (m_VertexArray != NULL)
		delete m_VertexArray;
	if (m_VertexBuffer != NULL)
		delete m_VertexBuffer;
	if (m_IndexBuffer != NULL)
		delete m_IndexBuffer;
}

void Mesh::SetVertices(float* vertices, uint32_t size)
{
	if (m_VertexArray != NULL)
		delete m_VertexArray;

	if (m_VertexBuffer != NULL)
		delete m_VertexBuffer;

	m_VertexBuffer = new VertexBuffer(vertices, size);
}

void Mesh::SetIndices(uint32_t* indices, uint32_t length)
{
	if (m_IndexBuffer != NULL)
		delete m_IndexBuffer;

	m_IndexBuffer = new IndexBuffer(indices, length);
}

void Mesh::Construct()
{
	if (m_VertexBuffer == NULL || m_VertexArray != NULL)
		return;
	
	m_VertexArray = new VertexArray();
	m_VertexArray->AddBuffer(*m_VertexBuffer, BufferLayout);
}

unsigned int Mesh::GetNumIndices() const { return m_IndexBuffer->GetCount(); }