#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

layout(binding = 0) buffer offsetBuffer
{
	float offsets[];
};

uniform mat4 u_Proj;

out vec3 v_Color;

void main()
{
	int index = gl_InstanceID * 3;
	vec4 vertexPos = vec4(vec3(position) / 4.0f, 0.0f);
	gl_Position = u_Proj * (vec4(offsets[index], offsets[index + 1], offsets[index + 2], 1.0f) + vertexPos);
	v_Color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 v_Color;

void main()
{
	fragColor = vec4(v_Color, 1.0f);
};
