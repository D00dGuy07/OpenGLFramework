#pragma once

#include "glm/glm.hpp"

#include "Util/GLFWEventWrapper.h"

// Forward declaration
struct GLFWwindow;

class FlyCamera
{
public:
	FlyCamera(GLFWwindow* window,
		glm::dvec3 position, glm::dvec2 rotation, double speed,
		double fov, double clipNear, double clipFar);
	~FlyCamera();

	glm::mat4 GetMatrix() { return m_Projection * m_CamMatrix; }

	void UpdateTransform();
private:
	// Projection stuff
	glm::mat4 m_Projection;

	double m_FOV;
	double m_ClipNear;
	double m_ClipFar;

	// Position stuff
	glm::mat4 m_CamMatrix;

	glm::dvec2 m_Rotation;
	glm::dvec3 m_Position;
	glm::dvec3 m_LookVector;
	double m_Speed;

	double m_LastUpdate;

	bool m_Focused = false;
	glm::dvec2 m_MousePrev;

	bool m_WPressed;
	bool m_APressed;
	bool m_SPressed;
	bool m_DPressed;

	void UpdateProjection(int32_t width, int32_t height);

	// Event Connections
	Ref<EventConnection<GLFWwindow*, int, int, int, int>> m_KeyPressedConnection;
	Ref<EventConnection<GLFWwindow*, double, double>> m_MousePosConnection;
	Ref<EventConnection<GLFWwindow*, int, int>> m_SizeChangeConnection;
};