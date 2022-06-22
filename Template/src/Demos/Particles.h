#pragma once

#include "Demo.h"

#include "glm/glm.hpp"

#include <vector>

class Shader;
class Mesh;
class UniformBuffer;
class Framebuffer;

class Particles : public Demo
{
public:
	Particles(GLFWwindow* window);

	virtual void run() override;

private:
	Mesh* m_ParticleMesh;
	Shader* m_ParticleShader;
	UniformBuffer* m_RenderData;

	Shader* m_PostShader;
	Mesh* m_PostMesh;
	Framebuffer* m_Framebuffer;

	glm::mat4 m_Projection;
	
	float m_LastFrameTime;

	struct ParticleDescriptor
	{
		glm::vec2 Position;
		glm::vec2 Velocity;

		float Rotation;
		float AngularVelocity;

		float Scale;
		glm::vec3 Color;
	};

	std::vector<ParticleDescriptor> m_ParticleData;

	ParticleDescriptor GenerateParticle();

	void Update();
	void Draw();
	void Free();
};