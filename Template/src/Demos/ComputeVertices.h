#pragma once

#include "Demo.h"

#include "glm/glm.hpp"

class Shader;
class ComputeShader;
class Mesh;
class Texture;
class ShaderBuffer;

class ComputeVertices : public Demo
{
public:
	ComputeVertices(GLFWwindow* window);

	virtual void run() override;
private:
	Mesh* m_SquareMesh;
	ShaderBuffer* m_OriginalVerts;
	Shader* m_RenderShader;
	ComputeShader* m_VerticesShader;
	glm::mat4 m_Projection;

	bool m_WireFrame = true;

	void Resize(const int& width, const int& height);
	void Draw();
	void Free();
};