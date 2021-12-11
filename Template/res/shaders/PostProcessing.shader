#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

void main()
{
	gl_Position = position;
	v_TexCoords = texCoords;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

uniform int u_Width;
uniform int u_Height;

void main()
{
    float offsetX = 1.0 / float(u_Width);
    float offsetY = 1.0 / float(u_Height);

    vec2 offsets[9] = vec2[](
        vec2(-offsetX, offsetY), // top-left
        vec2(0.0f, offsetY), // top-center
        vec2(offsetX, offsetY), // top-right
        vec2(-offsetX, 0.0f),   // center-left
        vec2(0.0f, 0.0f),   // center-center
        vec2(offsetX, 0.0f),   // center-right
        vec2(-offsetX, -offsetY), // bottom-left
        vec2(0.0f, -offsetY), // bottom-center
        vec2(offsetX, -offsetY)  // bottom-right    
        );

    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_Texture, v_TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

	fragColor = vec4(col, 1.0);
};
