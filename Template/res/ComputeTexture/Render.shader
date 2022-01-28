#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 u_Proj;

out vec2 v_TexCoords;

void main()
{
	gl_Position = position * u_Proj;
	v_TexCoords = texCoords;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
	fragColor = texture(u_Texture, v_TexCoords);
};
