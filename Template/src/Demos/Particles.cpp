#include "Demos/Particles.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"

#include "Util/GLFWEventWrapper.h"
#include "Util/Helpers.h"
#include "Util/Timer.h"

#include "glm/ext/matrix_clip_space.hpp"

#include <random>

constexpr int32_t ParticleCount = 2000;

Particles::Particles(GLFWwindow* window)
	: Demo(window),
	m_ParticleMesh(new Mesh()), m_ParticleShader(nullptr), m_RenderData(nullptr),
	m_PostShader(nullptr), m_PostMesh(new Mesh()),
	m_Projection(glm::ortho(-1.0f, 1.0f, -0.5625f, 0.5625f))
{
	// Load/Compile and initialize shader
	//if (FileHelpers::FileExists("res/Particles/Particle.shaderbin"))
	//	m_ParticleShader = new Shader("res/Particles/Particle.shaderbin", true);
	//else
		m_ParticleShader = new Shader("res/Particles/Particle.shader", false);
	m_ParticleShader->SetUniformMatrix4fv("u_Proj", &m_Projection, 1);

	//if (FileHelpers::FileExists("res/Particles/Post.shaderbin"))
	//	m_PostShader = new Shader("res/Particles/Post.shaderbin", true);
	//else
		m_PostShader = new Shader("res/Particles/Post.shader", false);
	m_PostShader->SetUniform1i("u_Texture", 0);
	m_PostShader->SetUniform2f("u_Res", glm::vec2(1280.0f, 720.0f));
	m_PostShader->SetUniform1f("u_Radius", 2.0f);

	// Create particle mesh
	float particleVertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	uint32_t particleIndices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_ParticleMesh->SetVertices(particleVertices, 4 * 4 * 2);
	m_ParticleMesh->SetIndices(particleIndices, 6);
	m_ParticleMesh->BufferLayout.Push<float>(2);
	m_ParticleMesh->Construct();

	// Generate particles
	for (int32_t i = 0; i < ParticleCount; i++)
		m_ParticleData.push_back(GenerateParticle());
	m_RenderData = new UniformBuffer(nullptr, 7 * ParticleCount * 4);
	m_RenderData->BindIndexed(0);

	// Post process render surface
	float postVertices[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
	};

	m_PostMesh->SetVertices(postVertices, 4 * 4 * 2);
	m_PostMesh->SetIndices(particleIndices, 6);
	m_PostMesh->BufferLayout.Push<float>(2);
	m_PostMesh->Construct();

	// Create and setup framebuffer
	FramebufferSpec spec = {
		1280U, 720U,
		{{ImageBufferType::Texture, FBOAttachmentType::Color, InternalImageFormat::RGBA8}},
		{{ImageBufferType::RenderBuffer, FBOAttachmentType::DepthStencil, InternalImageFormat::Depth24_Stencil8}}
	};

	m_Framebuffer = new Framebuffer(spec);
	static_cast<Texture*>(m_Framebuffer->GetColorAttachment(0).Buffer)->Bind();

	// Connect resizing
	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);
	wrapper->ConnectFramebufferSize(std::function<void(GLFWwindow*, int32_t, int32_t)>([&](GLFWwindow* window, int32_t width, int32_t height)
		{
			if (width < 1 || height < 1)
				return;

			Renderer::SetViewport(width, height);

			m_Framebuffer->Resize(width, height);
			m_PostShader->SetUniform2f("u_Res", glm::vec2(static_cast<float>(width), static_cast<float>(height)));

			if (width > height)
				m_Projection = glm::ortho(-1.0f, 1.0f, -((float)height / (float)width), ((float)height / (float)width));
			else if (height > width)
				m_Projection = glm::ortho(-((float)width / (float)height), ((float)width / (float)height), -1.0f, 1.0f);
			else if (height == width)
				m_Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
			m_ParticleShader->SetUniformMatrix4fv("u_Proj", &m_Projection, 1);

			Update();
			Draw();
		}
	));
}

Particles::ParticleDescriptor Particles::GenerateParticle()
{
	std::random_device dev;
	std::mt19937 rng(dev());

	std::uniform_real_distribution<float> velocityDist(-0.1f, 0.1f);
	std::uniform_real_distribution<float> angularDist(-45.0f, 45.0f);

	std::uniform_real_distribution<float> scaleDist(0.001f, 0.005f);
	std::uniform_real_distribution<float> colorDist(0.1f, 0.8f);

	return {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(velocityDist(rng), velocityDist(rng)),

		0.0f,
		angularDist(rng),

		scaleDist(rng),
		glm::vec3(colorDist(rng), colorDist(rng), colorDist(rng))
	};
}

void Particles::Draw()
{
	m_Framebuffer->Bind();
	Renderer::Clear();
	Renderer::SubmitMeshInstanced(*m_ParticleMesh, *m_ParticleShader, ParticleCount);
	m_Framebuffer->Unbind();

	Renderer::Clear();
	Renderer::SubmitMesh(*m_PostMesh, *m_PostShader);

	Renderer::DrawFrame();

	glfwSwapBuffers(m_WindowPointer);
}

void Particles::Update()
{
	float currentTime = static_cast<float>(glfwGetTime());
	float deltaTime = currentTime - m_LastFrameTime;
	m_LastFrameTime = currentTime;

	std::vector<float> renderData;
	for (auto& particle : m_ParticleData)
	{
		if (particle.Position.x < -1.0f || particle.Position.x > 1.0f || particle.Position.y < -1.0f || particle.Position.y > 1.0f)
			particle = GenerateParticle();
		else
		{
			particle.Position += particle.Velocity * deltaTime;
			particle.Rotation += particle.AngularVelocity * deltaTime;
		}

		renderData.push_back(particle.Position.x);
		renderData.push_back(particle.Position.y);
		renderData.push_back(glm::radians(particle.Rotation));
		renderData.push_back(particle.Scale);
		renderData.push_back(particle.Color.r);
		renderData.push_back(particle.Color.g);
		renderData.push_back(particle.Color.b);
	}

	m_RenderData->UpdateContents(renderData.data(), 0, static_cast<size_t>(7 * ParticleCount * 4));
}

void Particles::run()
{
	// Render loop
	while (!glfwWindowShouldClose(m_WindowPointer))
	{
		Update();
		Draw();
		glfwPollEvents();
	}

	ShaderBinary particleBinary = m_ParticleShader->GetBinary();
	particleBinary.WriteFile("res/Particles/Particle.shaderbin");
	particleBinary.Free();

	ShaderBinary postBinary = m_PostShader->GetBinary();
	postBinary.WriteFile("res/Particles/Post.shaderbin");
	postBinary.Free();

	Free();
	Renderer::DrawFrame();
}

void Particles::Free()
{
	delete m_ParticleMesh;
	delete m_ParticleShader;
	delete m_RenderData;
	delete m_PostMesh;
	delete m_PostShader;
	delete m_Framebuffer;
}