#version 300 es

precision mediump float;

in vec2 loc;

out vec4 color;

void	main()
{
	color = vec4(mod(loc, 1.0), 0, 1);
}
