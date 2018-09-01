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

	unsigned char test_texture1[] = {255, 255, 140, 255,
					100, 100, 100, 255,
					100, 100, 129, 255,
					255, 255, 255, 255};
	Texture t1 = {2, 2, test_texture1};

	unsigned char test_texture2[] = {22, 49, 140, 255,
                                        100, 200, 100, 255,
                                        100, 150, 129, 255,
                                        255, 255, 255, 255};
        Texture t2 = {2, 2, test_texture2};
	
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{1, 1.3, glm::vec2(0.3), t1.ID()});
	rects.push_back(Rectangle{0.4, 0.1, glm::vec2(-0.5), t2.ID()});
	
	Rectangle::Render(rects);
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
