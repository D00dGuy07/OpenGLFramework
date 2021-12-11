#pragma once

#include "glm/glm.hpp"

struct GLFWwindow;

class Shader;
class Mesh;

class Framebuffer;

class Example
{
public:
	Example(GLFWwindow* window);
	~Example();
	void run();
private:
	GLFWwindow* m_WindowPointer;

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
};