#pragma once

#include "GLFW/glfw3.h"

class Demo
{
public:
	Demo(GLFWwindow* window)
		: m_WindowPointer(window) {}
	virtual ~Demo() {}

	virtual void run() = 0;

protected:
	GLFWwindow* m_WindowPointer;
};