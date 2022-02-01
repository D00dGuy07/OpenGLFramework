#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_Proj;

void main()
{
	gl_Position = position * u_Proj;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = vec4(32.0f / 255.0f, 194.0f / 255.0f, 14.0f / 255.0f, 1.0f);
};
