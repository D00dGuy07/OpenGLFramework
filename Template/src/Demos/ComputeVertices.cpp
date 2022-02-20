#include "Demos/ComputeVertices.h"

// Renderer Includes
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/ShaderBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ComputeShader.h"
#include "Renderer/Texture.h"
#include "Renderer/GLHelpers.h"

// Util Includes
#include "Util/Helpers.h"
#include "Util/GLFWEventWrapper.h"

// glm
#include "glm/ext/matrix_clip_space.hpp"

template<typename T>
T lerp(T a, T b, T t)
{
	return (static_cast<T>(1) - t) * a + t * b;
}

const int32_t resolution = 30;

ComputeVertices::ComputeVertices(GLFWwindow* window)
	: Demo(window),
	m_RenderShader(NULL), m_VerticesShader(NULL),
	m_SquareMesh(new Mesh()), m_OriginalVerts(NULL),
	m_Projection(glm::ortho(-1.0f, 1.0f, -0.5625f, 0.5625f))
{
	// Load/Compile and initialize shaders

	if (FileHelpers::FileExists("res/ComputeVertices/Render.shaderbin"))
		m_RenderShader = new Shader("res/ComputeVertices/Render.shaderbin", true);
	else
	m_RenderShader = new Shader("res/ComputeVertices/Render.shader", false);

	if (FileHelpers::FileExists("res/ComputeVertices/Vertices.shaderbin"))
		m_VerticesShader = new ComputeShader("res/ComputeVertices/Vertices.shaderbin", true);
	else
	m_VerticesShader = new ComputeShader("res/ComputeVertices/Vertices.shader", false);

	m_RenderShader->SetUniformMatrix4f("u_Proj", m_Projection);

	m_VerticesShader->SetUniform1i("u_Resolution", resolution);

	// Construct mesh

	std::vector<glm::vec2> squareVertices;
	squareVertices.reserve(resolution * resolution);
	std::vector<uint32_t> squareIndices;
	squareIndices.reserve((resolution - 1) * (resolution - 1) * 6);

	for (int32_t y = 0; y < resolution; y++)
	{
		for (int32_t x = 0; x < resolution; x++)
		{
			squareVertices.emplace_back(
				lerp(-0.5f, 0.5f, static_cast<float>(x) / static_cast<float>(resolution - 1)),
				lerp(0.5f, -0.5f, static_cast<float>(y) / static_cast<float>(resolution - 1))
			);

			if (x != resolution - 1 && y != 0)
			{
				int32_t index = x + y * resolution;
				squareIndices.push_back(index);
				squareIndices.push_back(index + 1);
				squareIndices.push_back(index - resolution + 1);
				squareIndices.push_back(index - resolution + 1);
				squareIndices.push_back(index - resolution);
				squareIndices.push_back(index);
			}
		}
	}

	m_OriginalVerts = new ShaderBuffer(reinterpret_cast<float*>(squareVertices.data()), 8U * static_cast<uint32_t>(squareVertices.size()));
	m_OriginalVerts->BindIndexed(0);

	m_SquareMesh->SetVertices(reinterpret_cast<float*>(squareVertices.data()), 8U * static_cast<uint32_t>(squareVertices.size()));
	m_SquareMesh->SetIndices(squareIndices.data(), static_cast<uint32_t>(squareIndices.size()));
	m_SquareMesh->BufferLayout.Push<float>(2);
	m_SquareMesh->Construct();

	reinterpret_cast<ShaderBuffer*>(m_SquareMesh->GetVertexBuffer())->BindIndexed(1);

	// Connect resizing

	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);
	wrapper->ConnectFramebufferSize(std::function<void(GLFWwindow*, int, int)>([&](GLFWwindow* window, int width, int height)
		{
			Resize(width, height);
		}
	));

	// Set wire frame
	Renderer::Submit([]() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	});

	wrapper->ConnectMouseButton([&](GLFWwindow*, int button, int action, int) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			m_WireFrame = !m_WireFrame;
			if (m_WireFrame) {
				Renderer::Submit([]() {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				});
			}
			else
			{
				Renderer::Submit([]() {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				});
			}
		}
	});
}

void ComputeVertices::Resize(const int& width, const int& height)
{
	// Resize render output
	Renderer::Submit([width, height]() {
		glViewport(0, 0, width, height);
	});

	// Update projection to preserve the aspect ratio and send it to the shader
	if (width > height)
		m_Projection = glm::ortho(-1.0f, 1.0f, -((float)height / (float)width), ((float)height / (float)width));
	else if (height > width)
		m_Projection = glm::ortho(-((float)width / (float)height), ((float)width / (float)height), -1.0f, 1.0f);
	else if (height == width)
		m_Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	m_RenderShader->SetUniformMatrix4f("u_Proj", m_Projection);

	// Draw here because event polling hangs the render loop
	Draw();
}

void ComputeVertices::Draw()
{
	m_VerticesShader->SetUniform1f("u_Time", static_cast<float>(glfwGetTime()));
	m_VerticesShader->Dispatch(resolution, resolution, 1);
	GLMemoryHelper::Barrier(GLMemoryHelper::BarrierType::All);

	Renderer::Clear();
	Renderer::SubmitMesh(*m_SquareMesh, *m_RenderShader);
	Renderer::DrawFrame();

	glfwSwapBuffers(m_WindowPointer);
}

void ComputeVertices::run()
{
	// Render loop
	while (!glfwWindowShouldClose(m_WindowPointer))
	{
		Draw();
		glfwPollEvents();
	}

	ShaderBinary renderBinary = m_RenderShader->GetBinary();
	renderBinary.WriteFile("res/ComputeVertices/Render.shaderbin");
	renderBinary.Free();

	ShaderBinary verticesBinary = m_VerticesShader->GetBinary();
	verticesBinary.WriteFile("res/ComputeVertices/Vertices.shaderbin");
	verticesBinary.Free();

	Free();
	Renderer::DrawFrame();
}

void ComputeVertices::Free()
{
	delete m_SquareMesh;
	delete m_RenderShader;
	delete m_VerticesShader;
	delete m_OriginalVerts;
}