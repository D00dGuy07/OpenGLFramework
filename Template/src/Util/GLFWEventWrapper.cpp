// This file is automatically built by a script
#include <Util/GLFWEventWrapper.h>

#include <stdexcept>

std::unordered_map<GLFWwindow*, GLFWEventWrapper*> GLFWEventWrapper::m_Wrappers = std::unordered_map<GLFWwindow*, GLFWEventWrapper*>();

GLFWEventWrapper* GLFWEventWrapper::GetWrapper(GLFWwindow* window)
{
	try
	{
		return m_Wrappers.at(window);
	}
	catch (std::out_of_range)
	{
		GLFWEventWrapper* wrapper = new GLFWEventWrapper(window);
		m_Wrappers[window] = wrapper;
		return wrapper;
	}
}

// Auto gen bellow

GLFWEventWrapper::GLFWEventWrapper(GLFWwindow* window)
	: m_Window(window)
{
	glfwSetWindowSizeCallback(window, GLFWEventWrapper::FramebufferSizeCallback);
	glfwSetKeyCallback(window, GLFWEventWrapper::KeyPressedCallback);
	glfwSetWindowCloseCallback(window, GLFWEventWrapper::WindowCloseCallback);
}

void GLFWEventWrapper::DisposeWrapper(GLFWwindow* window)
{
	try
	{
		GLFWEventWrapper* wrapper = m_Wrappers.at(window);
		delete wrapper;

		glfwSetWindowSizeCallback(window, NULL);
		glfwSetKeyCallback(window, NULL);
		glfwSetWindowCloseCallback(window, NULL);
	}
	catch (std::out_of_range)
	{}
}


void GLFWEventWrapper::ConnectFramebufferSize(std::function<std::remove_pointer<GLFWframebuffersizefun>::type> callback)
{
	m_FramebufferSizeCallbacks.push_back(callback);
}

void GLFWEventWrapper::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_FramebufferSizeCallbacks)
		func(window, width, height);
}


void GLFWEventWrapper::ConnectKeyPressed(std::function<std::remove_pointer<GLFWkeyfun>::type> callback)
{
	m_KeyPressedCallbacks.push_back(callback);
}

void GLFWEventWrapper::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_KeyPressedCallbacks)
		func(window, key, scancode, action, mods);
}


void GLFWEventWrapper::ConnectWindowClose(std::function<std::remove_pointer<GLFWwindowclosefun>::type> callback)
{
	m_WindowCloseCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowCloseCallback(GLFWwindow* window)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowCloseCallbacks)
		func(window);

	DisposeWrapper(window);
}
