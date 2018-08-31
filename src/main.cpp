#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <vector>
#include <cstring>

#include "Rectangle.hpp"

void	test_render()
{
	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unsigned char test_texture[] = {255, 255, 140, 255,
					100, 100, 100, 255,
					100, 100, 129, 255,
					255, 255, 255, 255};
	Texture t = {2, 2, test_texture};
	Rectangle::Render(1, 1.3, glm::vec2(0.3), t.ID());
}

int	main(void)
{
	EmscriptenWebGLContextAttributes attrs;
	emscripten_webgl_init_context_attributes(&attrs);
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 2;
	attrs.minorVersion = 0;

	auto context = emscripten_webgl_create_context("canvas", &attrs);
	emscripten_webgl_make_context_current(context);

	emscripten_set_main_loop(test_render, 0, 0);
}
