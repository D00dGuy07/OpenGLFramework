#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 u_Proj;

out vec4 Color;

void main()
{
	gl_Position = position * u_Proj;
	Color = vec4(
		color.x,
		color.y,
		color.z,
		1.0f
	);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec4 Color;

void main()
{
	fragColor = Color;
};
