#shader compute
#version 430
layout(local_size_x = 1, local_size_y = 1) in;

layout(binding = 0) buffer originalData
{
	float inputData[];
};

layout(binding = 1) buffer newData
{
	float outputData[];
};

// Noise function: https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
vec3 permute(vec3 x) { return mod(((x * 34.0) + 1.0) * x, 289.0); }

float snoise(vec2 v) {
	const vec4 C = vec4(0.211324865405187, 0.366025403784439,
		-0.577350269189626, 0.024390243902439);
	vec2 i = floor(v + dot(v, C.yy));
	vec2 x0 = v - i + dot(i, C.xx);
	vec2 i1;
	i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	vec4 x12 = x0.xyxy + C.xxzz;
	x12.xy -= i1;
	i = mod(i, 289.0);
	vec3 p = permute(permute(i.y + vec3(0.0, i1.y, 1.0))
		+ i.x + vec3(0.0, i1.x, 1.0));
	vec3 m = max(0.5 - vec3(dot(x0, x0), dot(x12.xy, x12.xy),
		dot(x12.zw, x12.zw)), 0.0);
	m = m * m;
	m = m * m;
	vec3 x = 2.0 * fract(p * C.www) - 1.0;
	vec3 h = abs(x) - 0.5;
	vec3 ox = floor(x + 0.5);
	vec3 a0 = x - ox;
	m *= 1.79284291400159 - 0.85373472095314 * (a0 * a0 + h * h);
	vec3 g;
	g.x = a0.x * x0.x + h.x * x0.y;
	g.yz = a0.yz * x12.xz + h.yz * x12.yw;
	return 130.0 * dot(m, g);
}

uniform float u_Time;
uniform int u_Resolution;

#define SCALE 1.0f

void main()
{
	int index = (int(gl_GlobalInvocationID.x) + int(gl_GlobalInvocationID.y) * u_Resolution) * 2;
	vec2 coord = vec2(inputData[index], inputData[index + 1]);

	vec2 outCoord = vec2(
		coord.x + snoise(vec2(u_Time, coord.y * SCALE)) / 20.0f,
		coord.y + snoise(vec2(coord.x * SCALE, u_Time)) / 20.0f
	);
	outputData[index] = outCoord.x;
	outputData[index + 1] = outCoord.y;
}