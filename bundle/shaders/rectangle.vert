#version 300 es

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;

uniform vec2 dimension;
uniform vec2 center;
uniform float rotation;
uniform float aspect;

out vec2 uvCoor;

void	main()
{
	vec2 scaled_vertex = vertex * dimension;

	// apply rotation
	scaled_vertex = vec2(
		scaled_vertex.x * cos(angle) - scaled_vertex.y * sin(angle),
		scaled_vertex.x * sin(angle) + scaled_vertex.y * cos(angle));

	// apply aspect
	if (aspect > 1.0)
		scaled_vertex.x /= aspect;
	else
		scaled_vertex.y *= aspect;

	gl_Position = vec4(center + scaled_vertex, 0, 1);
	uvCoor = uv;
}
