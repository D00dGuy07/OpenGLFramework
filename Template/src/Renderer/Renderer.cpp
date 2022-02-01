#include "Renderer/Renderer.h"

#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Framebuffer.h"

RenderCommandQueue Renderer::m_CommandQueue = RenderCommandQueue();

void Renderer::SubmitMesh(Mesh& mesh, Shader& shader)
{
	if (mesh.m_VertexBuffer == NULL || mesh.m_IndexBuffer == NULL)
		return;

	if (mesh.m_VertexArray == NULL)
		mesh.Construct();

	shader.Bind();
	mesh.m_VertexArray->Bind();
	mesh.m_IndexBuffer->Bind();

	uint32_t indicesCount = mesh.GetNumIndices();
	Submit([indicesCount]() mutable {
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
	});
}

void Renderer::Clear()
{
	Submit([]() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	});
}

void Renderer::DrawFrame()
{
	m_CommandQueue.Execute();
}
