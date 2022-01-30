#pragma once

#include "Demo.h"

#include "glm/glm.hpp"

class Shader;
class ComputeShader;
class Mesh;
class Texture;

class ComputeTexture : public Demo
{
public:
	ComputeTexture(GLFWwindow* window);

	virtual void run() override;
private:
	Mesh* m_SquareMesh;
	Shader* m_RenderShader;
	ComputeShader* m_TextureShader;
	Texture* m_Texture;
	glm::mat4 m_Projection;

	void Resize(const int& width, const int& height);
	void Draw();
	void Free();
};