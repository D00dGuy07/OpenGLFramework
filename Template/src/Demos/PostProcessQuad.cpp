#include "Demos/PostProcessQuad.h"

// Rendering includes
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/RenderBuffer.h"

#include "Util/Helpers.h"

// glm includes
#include <glm/ext/matrix_clip_space.hpp>

// GLFW
#include "GLFW/glfw3.h"

#include "Util/GLFWEventWrapper.h"
#include <iostream>

PostProcessQuad::PostProcessQuad(GLFWwindow* window)
	: Demo(window), 
	m_SquareShader(NULL), m_SquareMesh(new Mesh()),
	m_Projection(glm::ortho(-1.0f, 1.0f, -0.5625f, 0.5625f)),
	m_PostShader(NULL), m_PostMesh(new Mesh())
{
	// Compile/Load shaders
	
	if (FileHelpers::FileExists("res/PostProcessQuad/Square.shaderbin"))
		m_SquareShader = new Shader("res/PostProcessQuad/Square.shaderbin", true);
	else
		m_SquareShader = new Shader("res/PostProcessQuad/Square.shader", false);

	if (FileHelpers::FileExists("res/PostProcessQuad/PostProcessing.shaderbin"))
		m_PostShader = new Shader("res/PostProcessQuad/PostProcessing.shaderbin", true);
	else
		m_PostShader = new Shader("res/PostProcessQuad/PostProcessing.shader", false);

	// Set up square mesh and shader

	float squareVertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f
	};

	unsigned int squareIndices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_SquareMesh->SetVertices(squareVertices, 4 * 4 * 5);
	m_SquareMesh->SetIndices(squareIndices, 6);
	m_SquareMesh->BufferLayout.Push<float>(2);
	m_SquareMesh->BufferLayout.Push<float>(3);
	m_SquareMesh->Construct();

	m_SquareShader->SetUniformMatrix4f("u_Proj", m_Projection);

	// Build framebuffer

	SetupFramebuffer(1280, 720);

	// Set up post processing mesh and shader

	float postVertices[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f
	};

	m_PostMesh->SetVertices(postVertices, 4 * 4 * 4);
	m_PostMesh->SetIndices(squareIndices, 6);
	m_PostMesh->BufferLayout.Push<float>(2);
	m_PostMesh->BufferLayout.Push<float>(2);
	m_PostMesh->Construct();

	m_PostShader->SetUniform1i("u_Texture", 0);
	m_PostShader->SetUniform1i("u_Width", 1280 / 4);
	m_PostShader->SetUniform1i("u_Height", 720 / 4);

	// Connect resizing

	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);
	wrapper->ConnectFramebufferSize(std::function<void(GLFWwindow*, int, int)>([&](GLFWwindow* window, int width, int height)
		{
			Resize(width, height);
		}
	));
}

PostProcessQuad::~PostProcessQuad()
{
	delete m_SquareMesh;
	delete m_SquareShader;
	delete m_PostMesh;
	delete m_PostShader;

	if (m_Framebuffer != NULL)
		delete m_Framebuffer;
}

void PostProcessQuad::Resize(const int& width, const int& height)
{
	if (width < 1 || height < 1)
		return;

	// Resize render output
	Renderer::Submit([width, height]() {
		glViewport(0, 0, width, height);
	});

	// Resize framebuffer
	m_Framebuffer->Resize(width, height);

	// Check completeness
	m_Framebuffer->Bind();

	// Update post processing shader
	m_PostShader->SetUniform1i("u_Width", width / 4);
	m_PostShader->SetUniform1i("u_Height", height / 4);

	// Update projection to preserve the aspect ratio and send it to the shader
	if (width > height)
		m_Projection = glm::ortho(-1.0f, 1.0f, -((float)height / (float)width), ((float)height / (float)width));
	else if (height > width)
		m_Projection = glm::ortho(-((float)width / (float)height), ((float)width / (float)height), -1.0f, 1.0f);
	else if (height == width)
		m_Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	m_SquareShader->SetUniformMatrix4f("u_Proj", m_Projection);

	// Draw here because event polling hangs the render loop
	Draw();
}

void PostProcessQuad::SetupFramebuffer(const int& width, const int& height)
{
	FramebufferSpec spec = {
		static_cast<uint32_t>(width), static_cast<uint32_t>(height),
		{{ImageBufferType::Texture, FBOAttachmentType::Color, InternalImageFormat::RGBA8}},
		{{ImageBufferType::RenderBuffer, FBOAttachmentType::DepthStencil, InternalImageFormat::Depth24_Stencil8}}
	};

	m_Framebuffer = new Framebuffer(spec);
	m_Framebuffer->Unbind();

	static_cast<Texture*>(m_Framebuffer->GetColorAttachment(0).Buffer)->Bind();
}

void PostProcessQuad::Draw()
{
	m_Framebuffer->Bind();
	Renderer::Clear();
	Renderer::SubmitMesh(*m_SquareMesh, *m_SquareShader);
	m_Framebuffer->Unbind();
	Renderer::Clear();
	Renderer::SubmitMesh(*m_PostMesh, *m_PostShader);

	Renderer::DrawFrame();

	glfwSwapBuffers(m_WindowPointer);
}

void PostProcessQuad::run()
{
	// Render loop
	while (!glfwWindowShouldClose(m_WindowPointer))
	{
		Draw();
		glfwPollEvents();
	}

	ShaderBinary squareBinary = m_SquareShader->GetBinary();
	squareBinary.WriteFile("res/PostProcessQuad/Square.shaderbin");
	squareBinary.Free();

	ShaderBinary postBinary = m_PostShader->GetBinary();
	postBinary.WriteFile("res/PostProcessQuad/PostProcessing.shaderbin");
	postBinary.Free();
}