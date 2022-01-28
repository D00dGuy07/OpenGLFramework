#shader compute
#version 430
layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba8, binding = 0) uniform image2D u_Texture;

const float PI = 3.1415926535897932384626433832795;

void main()
{
	ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);

	float r = sin((float(pixelCoords.x) * PI) / 20.0f) / 2.0f + 1.0f;
	float g = sin(((float(pixelCoords.x) - 7.5f) * PI) / 20.0f) / 2.0f + 1.0f;
	float b = sin(((float(pixelCoords.x) - 15.0f) * PI) / 20.0f) / 2.0f + 1.0f;

	vec4 pixel = vec4(r, g, b, 1.0f);

	imageStore(u_Texture, pixelCoords, pixel);
}