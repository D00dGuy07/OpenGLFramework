#include "Demos/InstancedCube.h"

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

constexpr int32_t Resolution = 101;

InstancedCube::InstancedCube(GLFWwindow* window)
	: Demo(window),
	m_RenderShader(NULL),
	m_CubeMesh(new Mesh()), m_Instances(NULL),
	m_Camera(window, glm::dvec3(0.0, 0.0, 0.0), glm::dvec2(0.0, 0.0), 10.0, 70.0, 0.1, 1000.0)
{
	// Load/Compile and initialize shaders

	if (FileHelpers::FileExists("res/InstancedCube/Render.shaderbin"))
		m_RenderShader = new Shader("res/InstancedCube/Render.shaderbin", true);
	else
	m_RenderShader = new Shader("res/InstancedCube/Render.shader", false);

	// Construct mesh

	glm::vec3 cubeVertices[] = {
		glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.7f, 0.1f, 0.2f),
		glm::vec3( 0.5f, -0.5f,  0.5f),	glm::vec3(0.2f, 0.1f, 0.7f),
		glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.7f, 0.1f, 0.2f),
		glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.2f, 0.1f, 0.7f),
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.1f, 0.2f),
		glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.2f, 0.1f, 0.7f),
		glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.7f, 0.1f, 0.2f),
		glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.2f, 0.1f, 0.7f)
	};

	glm::uvec3 cubeIndices[] = {

		// Front face
		glm::uvec3(0, 1, 2),
		glm::uvec3(2, 3, 0),

		// Back face
		glm::uvec3(5, 4, 7),
		glm::uvec3(7, 6, 5),

		// Left face
		glm::uvec3(4, 0, 3),
		glm::uvec3(3, 7, 4),

		// Right face
		glm::uvec3(1, 5, 6),
		glm::uvec3(6, 2, 1),

		// Top face
		glm::uvec3(3, 2, 6),
		glm::uvec3(6, 7, 3),

		// Bottom face
		glm::uvec3(4, 5, 1),
		glm::uvec3(1, 0, 4)
	};

	m_CubeMesh->SetVertices(reinterpret_cast<float*>(cubeVertices), 8 * 6 * sizeof(float));
	m_CubeMesh->SetIndices(reinterpret_cast<uint32_t*>(cubeIndices), 36);
	m_CubeMesh->BufferLayout.Push<float>(3);
	m_CubeMesh->BufferLayout.Push<float>(3);
	m_CubeMesh->Construct();

	auto positions = std::vector<glm::vec3>();
	positions.reserve(Resolution * Resolution * Resolution);

	int32_t bound = (Resolution - 1) / 2;
	for (int32_t y = -bound; y <= bound; y++)
	{
		for (int32_t z = -bound; z <= bound; z++)
		{
			for (int32_t x = -bound; x <= bound; x++)
			{
				positions.emplace_back(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
			}
		}
	}

	m_Instances = new ShaderBuffer(reinterpret_cast<float*>(positions.data()), 12U * static_cast<uint32_t>(positions.size()));
	m_Instances->BindIndexed(0);

	// Connect resizing
	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);
	wrapper->ConnectFramebufferSize(std::function<void(GLFWwindow*, int, int)>([&](GLFWwindow* window, int, int)
		{
			Draw();
		}
	));

	// Set some stuff for 3D
	Renderer::Submit([]() {
		// Enable Depth test
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Enable Culling
		glEnable(GL_CULL_FACE);
	});
}

void InstancedCube::Draw()
{
	Renderer::Clear();

	m_Camera.UpdateTransform();
	glm::mat4 matrix = m_Camera.GetMatrix();
	m_RenderShader->SetUniformMatrix4fv("u_Proj", &matrix, 1);
	
	Renderer::SubmitMeshInstanced(*m_CubeMesh, *m_RenderShader, Resolution * Resolution * Resolution);
	//Renderer::SubmitMesh(*m_CubeMesh, *m_RenderShader);
	Renderer::DrawFrame();

	glfwSwapBuffers(m_WindowPointer);
}

void InstancedCube::run()
{
	// Render loop
	while (!glfwWindowShouldClose(m_WindowPointer))
	{
		Draw();
		glfwPollEvents();
	}

	ShaderBinary renderBinary = m_RenderShader->GetBinary();
	renderBinary.WriteFile("res/InstancedCube/Render.shaderbin");
	renderBinary.Free();

	Free();
	Renderer::DrawFrame();
}

void InstancedCube::Free()
{
	delete m_CubeMesh;
	delete m_RenderShader;
	delete m_Instances;
}