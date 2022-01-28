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

// Auto gen below

GLFWEventWrapper::GLFWEventWrapper(GLFWwindow* window)
	: m_Window(window)
{
	glfwSetMouseButtonCallback(window, GLFWEventWrapper::MouseButtonCallback);
	glfwSetCursorPosCallback(window, GLFWEventWrapper::MouseCursorPosCallback);
	glfwSetCursorEnterCallback(window, GLFWEventWrapper::MouseCursorEnterCallback);
	glfwSetScrollCallback(window, GLFWEventWrapper::MouseScrollCallback);
	glfwSetCharCallback(window, GLFWEventWrapper::CharCallback);
	glfwSetCharModsCallback(window, GLFWEventWrapper::CharModsCallback);
	glfwSetDropCallback(window, GLFWEventWrapper::PathDropCallback);
	glfwSetWindowPosCallback(window, GLFWEventWrapper::WindowPosCallback);
	glfwSetWindowSizeCallback(window, GLFWEventWrapper::WindowSizeCallback);
	glfwSetWindowRefreshCallback(window, GLFWEventWrapper::WindowRefreshCallback);
	glfwSetWindowFocusCallback(window, GLFWEventWrapper::WindowFocusCallback);
	glfwSetWindowIconifyCallback(window, GLFWEventWrapper::WindowIconifyCallback);
	glfwSetWindowMaximizeCallback(window, GLFWEventWrapper::WindowMaximizeCallback);
	glfwSetFramebufferSizeCallback(window, GLFWEventWrapper::FramebufferSizeCallback);
	glfwSetWindowContentScaleCallback(window, GLFWEventWrapper::WindowContentScaleCallback);
	glfwSetWindowCloseCallback(window, GLFWEventWrapper::WindowCloseCallback);
}

void GLFWEventWrapper::DisposeWrapper(GLFWwindow* window)
{
	try
	{
		GLFWEventWrapper* wrapper = m_Wrappers.at(window);
		delete wrapper;

		glfwSetMouseButtonCallback(window, NULL);
		glfwSetCursorPosCallback(window, NULL);
		glfwSetCursorEnterCallback(window, NULL);
		glfwSetScrollCallback(window, NULL);
		glfwSetCharCallback(window, NULL);
		glfwSetCharModsCallback(window, NULL);
		glfwSetDropCallback(window, NULL);
		glfwSetWindowPosCallback(window, NULL);
		glfwSetWindowSizeCallback(window, NULL);
		glfwSetWindowRefreshCallback(window, NULL);
		glfwSetWindowFocusCallback(window, NULL);
		glfwSetWindowIconifyCallback(window, NULL);
		glfwSetWindowMaximizeCallback(window, NULL);
		glfwSetFramebufferSizeCallback(window, NULL);
		glfwSetWindowContentScaleCallback(window, NULL);
		glfwSetWindowCloseCallback(window, NULL);
	}
	catch (std::out_of_range)
	{}
}


void GLFWEventWrapper::ConnectMouseButton(std::function<std::remove_pointer<GLFWmousebuttonfun>::type> callback)
{
	m_MouseButtonCallbacks.push_back(callback);
}

void GLFWEventWrapper::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_MouseButtonCallbacks)
		func(window, button, action, mods);
}


void GLFWEventWrapper::ConnectMouseCursorPos(std::function<std::remove_pointer<GLFWcursorposfun>::type> callback)
{
	m_MouseCursorPosCallbacks.push_back(callback);
}

void GLFWEventWrapper::MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_MouseCursorPosCallbacks)
		func(window, xpos, ypos);
}


void GLFWEventWrapper::ConnectMouseCursorEnter(std::function<std::remove_pointer<GLFWcursorenterfun>::type> callback)
{
	m_MouseCursorEnterCallbacks.push_back(callback);
}

void GLFWEventWrapper::MouseCursorEnterCallback(GLFWwindow* window, int entered)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_MouseCursorEnterCallbacks)
		func(window, entered);
}


void GLFWEventWrapper::ConnectMouseScroll(std::function<std::remove_pointer<GLFWscrollfun>::type> callback)
{
	m_MouseScrollCallbacks.push_back(callback);
}

void GLFWEventWrapper::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_MouseScrollCallbacks)
		func(window, xoffset, yoffset);
}


void GLFWEventWrapper::ConnectChar(std::function<std::remove_pointer<GLFWcharfun>::type> callback)
{
	m_CharCallbacks.push_back(callback);
}

void GLFWEventWrapper::CharCallback(GLFWwindow* window, unsigned int codepoint)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_CharCallbacks)
		func(window, codepoint);
}


void GLFWEventWrapper::ConnectCharMods(std::function<std::remove_pointer<GLFWcharmodsfun>::type> callback)
{
	m_CharModsCallbacks.push_back(callback);
}

void GLFWEventWrapper::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_CharModsCallbacks)
		func(window, codepoint, mods);
}


void GLFWEventWrapper::ConnectPathDrop(std::function<std::remove_pointer<GLFWdropfun>::type> callback)
{
	m_PathDropCallbacks.push_back(callback);
}

void GLFWEventWrapper::PathDropCallback(GLFWwindow* window, int path_count, const char* paths[])
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_PathDropCallbacks)
		func(window, path_count, paths);
}


void GLFWEventWrapper::ConnectWindowPos(std::function<std::remove_pointer<GLFWwindowposfun>::type> callback)
{
	m_WindowPosCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowPosCallbacks)
		func(window, xpos, ypos);
}


void GLFWEventWrapper::ConnectWindowSize(std::function<std::remove_pointer<GLFWwindowsizefun>::type> callback)
{
	m_WindowSizeCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowSizeCallbacks)
		func(window, width, height);
}


void GLFWEventWrapper::ConnectWindowRefresh(std::function<std::remove_pointer<GLFWwindowrefreshfun>::type> callback)
{
	m_WindowRefreshCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowRefreshCallback(GLFWwindow* window)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowRefreshCallbacks)
		func(window);
}


void GLFWEventWrapper::ConnectWindowFocus(std::function<std::remove_pointer<GLFWwindowfocusfun>::type> callback)
{
	m_WindowFocusCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowFocusCallback(GLFWwindow* window, int focused)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowFocusCallbacks)
		func(window, focused);
}


void GLFWEventWrapper::ConnectWindowIconify(std::function<std::remove_pointer<GLFWwindowiconifyfun>::type> callback)
{
	m_WindowIconifyCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowIconifyCallback(GLFWwindow* window, int iconified)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowIconifyCallbacks)
		func(window, iconified);
}


void GLFWEventWrapper::ConnectWindowMaximize(std::function<std::remove_pointer<GLFWwindowmaximizefun>::type> callback)
{
	m_WindowMaximizeCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowMaximizeCallback(GLFWwindow* window, int maximized)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowMaximizeCallbacks)
		func(window, maximized);
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


void GLFWEventWrapper::ConnectWindowContentScale(std::function<std::remove_pointer<GLFWwindowcontentscalefun>::type> callback)
{
	m_WindowContentScaleCallbacks.push_back(callback);
}

void GLFWEventWrapper::WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
	GLFWEventWrapper* wrapper = GetWrapper(window);
	for (auto func : wrapper->m_WindowContentScaleCallbacks)
		func(window, xscale, yscale);
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
