#pragma once

#include "Demo.h"

#include "glm/glm.hpp"

#include "Common/FlyCamera.h"

class Shader;
class Mesh;
class ShaderBuffer;

class InstancedCube : public Demo
{
public:
	InstancedCube(GLFWwindow* window);

	virtual void run() override;
private:
	Mesh* m_CubeMesh;
	ShaderBuffer* m_Instances;
	Shader* m_RenderShader;
	FlyCamera m_Camera;

	void Draw();
	void Free();
};