// This file is automatically built by a script
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
	void ConnectMouseButton(std::function<std::remove_pointer<GLFWmousebuttonfun>::type> callback);
	void ConnectMouseCursorPos(std::function<std::remove_pointer<GLFWcursorposfun>::type> callback);
	void ConnectMouseCursorEnter(std::function<std::remove_pointer<GLFWcursorenterfun>::type> callback);
	void ConnectMouseScroll(std::function<std::remove_pointer<GLFWscrollfun>::type> callback);
	void ConnectChar(std::function<std::remove_pointer<GLFWcharfun>::type> callback);
	void ConnectCharMods(std::function<std::remove_pointer<GLFWcharmodsfun>::type> callback);
	void ConnectPathDrop(std::function<std::remove_pointer<GLFWdropfun>::type> callback);
	void ConnectWindowPos(std::function<std::remove_pointer<GLFWwindowposfun>::type> callback);
	void ConnectWindowSize(std::function<std::remove_pointer<GLFWwindowsizefun>::type> callback);
	void ConnectWindowRefresh(std::function<std::remove_pointer<GLFWwindowrefreshfun>::type> callback);
	void ConnectWindowFocus(std::function<std::remove_pointer<GLFWwindowfocusfun>::type> callback);
	void ConnectWindowIconify(std::function<std::remove_pointer<GLFWwindowiconifyfun>::type> callback);
	void ConnectWindowMaximize(std::function<std::remove_pointer<GLFWwindowmaximizefun>::type> callback);
	void ConnectFramebufferSize(std::function<std::remove_pointer<GLFWframebuffersizefun>::type> callback);
	void ConnectWindowContentScale(std::function<std::remove_pointer<GLFWwindowcontentscalefun>::type> callback);
	void ConnectWindowClose(std::function<std::remove_pointer<GLFWwindowclosefun>::type> callback);
	// End Auto Gen
private:
	// Factory definitions
	static std::unordered_map<GLFWwindow*, GLFWEventWrapper*> m_Wrappers;

	static void DisposeWrapper(GLFWwindow* window);

	// Auto Gen
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseCursorEnterCallback(GLFWwindow* window, int entered);
	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void CharCallback(GLFWwindow* window, unsigned int codepoint);
	static void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	static void PathDropCallback(GLFWwindow* window, int path_count, const char* paths[]);
	static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos);
	static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	static void WindowRefreshCallback(GLFWwindow* window);
	static void WindowFocusCallback(GLFWwindow* window, int focused);
	static void WindowIconifyCallback(GLFWwindow* window, int iconified);
	static void WindowMaximizeCallback(GLFWwindow* window, int maximized);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
	static void WindowCloseCallback(GLFWwindow* window);
	// End Auto Gen

	// Object definitions
	GLFWwindow* m_Window;

	// Auto Gen
	std::vector<std::function<std::remove_pointer<GLFWmousebuttonfun>::type>> m_MouseButtonCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWcursorposfun>::type>> m_MouseCursorPosCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWcursorenterfun>::type>> m_MouseCursorEnterCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWscrollfun>::type>> m_MouseScrollCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWcharfun>::type>> m_CharCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWcharmodsfun>::type>> m_CharModsCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWdropfun>::type>> m_PathDropCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowposfun>::type>> m_WindowPosCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowsizefun>::type>> m_WindowSizeCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowrefreshfun>::type>> m_WindowRefreshCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowfocusfun>::type>> m_WindowFocusCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowiconifyfun>::type>> m_WindowIconifyCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowmaximizefun>::type>> m_WindowMaximizeCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWframebuffersizefun>::type>> m_FramebufferSizeCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowcontentscalefun>::type>> m_WindowContentScaleCallbacks;
	std::vector<std::function<std::remove_pointer<GLFWwindowclosefun>::type>> m_WindowCloseCallbacks;
	// End Auto Gen

	GLFWEventWrapper(GLFWwindow* window);
};