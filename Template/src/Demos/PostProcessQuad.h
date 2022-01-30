#pragma once

#include "Demo.h"

#include "glm/glm.hpp"

class Shader;
class Mesh;

class Framebuffer;

class PostProcessQuad : public Demo
{
public:
	PostProcessQuad(GLFWwindow* window);

	virtual void run() override;
private:
	// Colored square data
	Shader* m_SquareShader;
	Mesh* m_SquareMesh;
	glm::mat4 m_Projection;

	// Post processing data
	Shader* m_PostShader;
	Mesh* m_PostMesh;

	// Offscreen framebuffer data
	Framebuffer* m_Framebuffer;

	void Resize(const int& width, const int& height);
	void SetupFramebuffer(const int& width, const int& height);
	void Draw();
	void Free();
};