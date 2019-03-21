#include <iostream>
#include <vector>
#include <cstring>

#include "GLWindow.hpp"
#include "Rectangle.hpp"
#include "Input.hpp"

void	test_render(void* arg)
{
	Input* input = (Input*)arg;

	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unsigned char test_texture1[] = {255, 255, 140, 255,
					100, 100, 100, 255,
					100, 100, 129, 255,
					255, 255, 255, 255};
	Texture t1 = {2, 2, test_texture1};

	Texture t2 = Texture::GenerateFromSVG("assets/svg_test.svg", 10);
	Texture t3 = t2;
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{1, 1.3, glm::vec2(0.3), t1.ID()});
	rects.push_back(Rectangle{0.4, 0.1, glm::vec2(-0.5), t2.ID()});
	rects.push_back(Rectangle{0.1, 0.3, glm::vec2(0), t3.ID()});

	Rectangle::Render(rects);

	std::cout << input->MouseDown(0) << std::endl;
}

int	main(void)
{
	GLWindow* window = new GLWindow("canvas");
	Input* input = new Input("body");

	(void)window;

	emscripten_set_main_loop_arg(test_render, input, 0, 0);
}
