#pragma once

#include <unordered_map>
#include <functional>

#include "GLFW/glfw3.h"

class GLFWEventWrapper
{
public:
	// Factory definitions
	static GLFWEventWrapper* GetWrapper(GLFWwindow* window);

	// Auto Gen
	void ConnectFramebufferSize(std::function<std::remove_pointer<GLFWframebuffersizefun>::type> callback);
	void ConnectWindowClose(std::function<std::remove_pointer<GLFWwindowclosefun>::type> callback);
	// End Auto Gen
private:
	// Factory definitions
	static std::unordered_map<GLFWwindow*, GLFWEventWrapper*> m_Wrappers;

	static void DisposeWrapper(GLFWwindow* window);

	// Auto Gen
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void WindowCloseCallback(GLFWwindow* window);
	// End Auto Gen

	// Object definitions
	GLFWwindow* m_Window;

	// Auto Gen
	std::vector<std::function<std::remove_pointer<GLFWframebuffersizefun>::type>> m_FramebufferSizeCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowclosefun>::type>> m_WindowCloseCallbacks;
	// End Auto Gen

	GLFWEventWrapper(GLFWwindow* window);
};