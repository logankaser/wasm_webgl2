#version 300 es

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;

uniform vec2 dimension;
uniform vec2 center;

out vec2 uvCoor;

void	main()
{
	gl_Position = vec4(center + vertex * dimension, 0, 1);
	uvCoor = uv;
}
