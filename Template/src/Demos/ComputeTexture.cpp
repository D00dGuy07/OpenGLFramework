#include "Demos/ComputeTexture.h"

// Renderer Includes
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/ComputeShader.h"
#include "Renderer/Texture.h"
#include "Renderer/GLHelpers.h"

// Util Includes
#include "Util/Helpers.h"
#include "Util/GLFWEventWrapper.h"

// glm
#include <glm/ext/matrix_clip_space.hpp>

ComputeTexture::ComputeTexture(GLFWwindow* window)
	: Demo(window),
	m_RenderShader(NULL), m_TextureShader(NULL),
	m_SquareMesh(new Mesh()),
	m_Projection(glm::ortho(-1.0f, 1.0f, -0.5625f, 0.5625f)),
	m_Texture(new Texture(256, 256, InternalImageFormat::RGBA8))
{
	// Load/Compile and initialize shaders

	//if (FileHelpers::FileExists("res/ComputeTexture/Render.shaderbin"))
	//	m_RenderShader = new Shader("res/ComputeTexture/Render.shaderbin", true);
	//else
		m_RenderShader = new Shader("res/ComputeTexture/Render.shader", false);

	//if (FileHelpers::FileExists("res/ComputeTexture/Texture.shaderbin"))
	//	m_TextureShader = new ComputeShader("res/ComputeTexture/Texture.shaderbin", true);
	//else
		m_TextureShader = new ComputeShader("res/ComputeTexture/Texture.shader", false);

	m_Texture->Bind();
	m_Texture->BindImage();

	m_RenderShader->SetUniformMatrix4f("u_Proj", m_Projection);
	m_RenderShader->SetUniform1i("u_Texture", 0);

	m_TextureShader->SetUniform1i("u_Texture", 0);

	// Construct mesh

	float squareVertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f
	};

	unsigned int squareIndices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_SquareMesh->SetVertices(squareVertices, 4 * 4 * 5);
	m_SquareMesh->SetIndices(squareIndices, 6);
	m_SquareMesh->BufferLayout.Push<float>(2);
	m_SquareMesh->BufferLayout.Push<float>(2);
	m_SquareMesh->Construct();

	// Connect resizing

	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);
	wrapper->ConnectFramebufferSize(std::function<void(GLFWwindow*, int, int)>([&](GLFWwindow* window, int width, int height)
		{
			Resize(width, height);
		}
	));

	// Render Texture
	m_TextureShader->Dispatch(256, 256, 1);
	GLMemoryHelper::Barrier(GLMemoryHelper::BarrierType::ShaderImgAccess);
}

ComputeTexture::~ComputeTexture()
{
	delete m_SquareMesh;
	delete m_RenderShader;
	delete m_TextureShader;
	delete m_Texture;
}

void ComputeTexture::Resize(const int& width, const int& height)
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

void ComputeTexture::Draw()
{
	m_TextureShader->Dispatch(256, 256, 1);
	GLMemoryHelper::Barrier(GLMemoryHelper::BarrierType::ShaderImgAccess);
	// Nothing special happening in here
	Renderer::Clear();
	Renderer::SubmitMesh(*m_SquareMesh, *m_RenderShader);
	Renderer::DrawFrame();

	glfwSwapBuffers(m_WindowPointer);
}

void ComputeTexture::run()
{
	// Render loop
	while (!glfwWindowShouldClose(m_WindowPointer))
	{
		Draw();
		glfwPollEvents();
	}

	ShaderBinary renderBinary = m_RenderShader->GetBinary();
	renderBinary.WriteFile("res/ComputeTexture/Render.shaderbin");
	renderBinary.Free();

	ShaderBinary textureBinary = m_TextureShader->GetBinary();
	textureBinary.WriteFile("res/ComputeTexture/Texture.shaderbin");
	textureBinary.Free();
}