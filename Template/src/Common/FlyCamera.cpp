#include "Common/FlyCamera.h"

// glm
#include <glm/ext/matrix_clip_space.hpp>
#include "glm/gtc/matrix_transform.hpp"

// Other
#include "Renderer/Renderer.h"

FlyCamera::FlyCamera(GLFWwindow* window,
	glm::dvec3 position, glm::dvec2 rotation, double speed,
	double fov, double clipNear, double clipFar)
	: m_Position(position), m_Rotation(rotation), m_Speed(speed),
	m_FOV(fov), m_ClipNear(clipNear), m_ClipFar(clipFar)
{
	// Init

	glfwGetCursorPos(window, &m_MousePrev.x, &m_MousePrev.y);

	int32_t width, height;
	glfwGetFramebufferSize(window, &width, &height);
	m_Projection = glm::perspective(static_cast<float>(glm::radians(m_FOV)),
		static_cast<float>(width) / static_cast<float>(height),
		static_cast<float>(m_ClipNear), static_cast<float>(m_ClipFar));

	UpdateTransform();

	// Events
	GLFWEventWrapper* wrapper = GLFWEventWrapper::GetWrapper(window);

	m_KeyPressedConnection = wrapper->ConnectKey([&](GLFWwindow* window, int key, int scancode, int action, int mods) {
		// Handles WASD input and escape key for focusing and unfocusing the camera
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS)
			{
				// Toggle cursor when escape is pressed
				if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					m_Focused = true;
					// Reset the previous cursor position because the user probably moved 
					// the mouse since the camera was last focused
					glfwGetCursorPos(window, &m_MousePrev.x, &m_MousePrev.y);
				}
				else
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					m_Focused = false;
				}
			}
			return;
		case GLFW_KEY_W:
			m_WPressed = (action == GLFW_PRESS) ? true : (action == GLFW_RELEASE) ? false : m_WPressed;
			break;
		case GLFW_KEY_A:
			m_APressed = (action == GLFW_PRESS) ? true : (action == GLFW_RELEASE) ? false : m_APressed;
			break;
		case GLFW_KEY_S:
			m_SPressed = (action == GLFW_PRESS) ? true : (action == GLFW_RELEASE) ? false : m_SPressed;
			break;
		case GLFW_KEY_D:
			m_DPressed = (action == GLFW_PRESS) ? true : (action == GLFW_RELEASE) ? false : m_DPressed;
			break;
		default:
			break;
		}
	});

	m_MousePosConnection = wrapper->ConnectMouseCursorPos([&](GLFWwindow*, double x, double y) {
		if (m_Focused)
		{
			glm::dvec2 currentPos(x, y);
			glm::dvec2 difference = currentPos - m_MousePrev;
			m_MousePrev = currentPos;

			m_Rotation -= glm::dvec2(difference.x / 5.0, difference.y / 5.0);

			if (m_Rotation.y > 89.0)
				m_Rotation.y = 89.0;
			else if (m_Rotation.y < -89.0)
				m_Rotation.y = -89.0;

			UpdateTransform();
		}
	});

	m_SizeChangeConnection = wrapper->ConnectFramebufferSize([&](GLFWwindow*, int width, int height) {
		UpdateProjection(width, height);
	});
}

FlyCamera::~FlyCamera()
{
	m_KeyPressedConnection->Disconnect();
	m_MousePosConnection->Disconnect();
	m_SizeChangeConnection->Disconnect();
}

void FlyCamera::UpdateTransform()
{
	const glm::dvec3 UP(0.0, 1.0, 0.0);

	// Calculate delta time
	double deltaTime;
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - m_LastUpdate;
		m_LastUpdate = currentTime;
	}

	// Calculate look vector
	{
		double y = std::sin(glm::radians(m_Rotation.y));
		double r = std::cos(glm::radians(m_Rotation.y));
		double x = std::sin(glm::radians(m_Rotation.x)) * r;
		double z = std::cos(glm::radians(m_Rotation.x)) * r;
		m_LookVector = glm::dvec3(x, y, z);
	}

	// Calculate right vector
	glm::dvec3 right = glm::cross(m_LookVector, UP);

	// Update position
	if (m_Focused)
	{
		glm::dvec3 moveVector(0.0, 0.0, 0.0);
		if (m_WPressed)
			moveVector += m_LookVector;
		if (m_SPressed)
			moveVector += -m_LookVector;
		if (m_APressed)
			moveVector += -right;
		if (m_DPressed)
			moveVector += right;

		if (moveVector != glm::dvec3(0.0, 0.0, 0.0))
			m_Position += glm::normalize(moveVector) * m_Speed * deltaTime;
	}
	
	glm::dvec3 lookPosition = m_Position + m_LookVector;
	m_CamMatrix = glm::lookAt(
		glm::vec3(static_cast<float>(m_Position.x), static_cast<float>(m_Position.y), static_cast<float>(m_Position.z)),
		glm::vec3(static_cast<float>(lookPosition.x), static_cast<float>(lookPosition.y), static_cast<float>(lookPosition.z)),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void FlyCamera::UpdateProjection(int32_t width, int32_t height)
{
	if (width != 0 && height != 0)
	{
		m_Projection = glm::perspective(static_cast<float>(glm::radians(m_FOV)),
			static_cast<float>(width) / static_cast<float>(height),
			static_cast<float>(m_ClipNear), static_cast<float>(m_ClipFar));
		Renderer::Submit([width, height]() {
			glViewport(0, 0, width, height);
		});
	}
}