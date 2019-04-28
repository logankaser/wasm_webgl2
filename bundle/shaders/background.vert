#version 300 es

layout (location = 0) in vec2 vertex;

uniform vec2 campos;
uniform float scale;
uniform float aspect;

out vec2 loc;

void	main()
{
	gl_Position = vec4(vertex, 0, 1);
	if (aspect > 1.0)
		loc = vec2(vertex.x * aspect, vertex.y) * scale;
	else
		loc = vec2(vertex.x, vertex.y / aspect) * scale;
}
