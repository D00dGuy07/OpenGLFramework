#include <iostream>

#include "Util/GLFWLoad.h"

// Demos
#include "Demos/PostProcessQuad.h"
#include "Demos/ComputeTexture.h"
#include "Demos/ComputeVertices.h"

// Enable Nvidia high performace graphics
#include <windows.h>
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(void)
{
	// Load OpenGL/GLFW
	GLFWwindow* window = LoadGLFW(1280, 720);

	if (window == NULL)
		return -1;

	// Run application
	Demo* demo = new ComputeVertices(window);
	demo->run();
    delete demo;

	// Clean stuff up
	glfwTerminate();

	return 0;
}