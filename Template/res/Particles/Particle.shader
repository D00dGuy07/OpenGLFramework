#shader vertex
#version 430 core

layout(location = 0) in vec4 position;

layout(binding = 0) uniform dataBuffer
{
	float data[14000];
};

uniform mat4 u_Proj;

out vec3 v_Color;

vec2 Rotate(vec2 original, float theta)
{
	return vec2(
		(original.x * cos(theta) - original.y * sin(theta)),
		(original.x * sin(theta) + original.y * cos(theta))
	);
}

void main()
{
	int index = gl_InstanceID * 7;
	
	vec2 offset = vec2(data[index], data[index + 1]);
	float rotation = data[index + 2];
	float scale = data[index + 3];

	//gl_Position = vec4((Rotate(position.xy, rotation) * scale + offset) / m_Resolution * 2.0f - 1.0f, position.zw);
	gl_Position = u_Proj * vec4(Rotate(position.xy, rotation) * scale + offset, position.zw);
	//gl_Position = position;
	v_Color = vec3(data[index + 4], data[index + 5], data[index + 6]);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 v_Color;

void main()
{
	fragColor = vec4(v_Color, 1.0f);
	//fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};
