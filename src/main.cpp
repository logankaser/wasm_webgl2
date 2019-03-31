#include <iostream>
#include <vector>
#include <cstring>
#include <stdint.h>

#include "GLWindow.hpp"
#include "Rectangle.hpp"
#include "Input.hpp"

enum TextureMode : uint8_t {
	nearest = 0,
	mipmap = 1
};

extern "C" void __generate_texture(const char* identifier, size_t len, uint8_t mode, uint32_t* id);
GLuint generate_texture(const std::string& identifier, TextureMode mode)
{
	uint32_t id;
	__generate_texture(identifier.data(), identifier.length(), static_cast<uint8_t>(mode), &id);
	return id;
}

void	test_render(void* arg)
{
	Input* input = static_cast<Input*>(arg);

	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint id = generate_texture("circle", TextureMode::mipmap);

	Texture test = {id};

	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{1.0, 1.0, glm::vec2(0.0), test.ID()});
	Rectangle::Render(rects);

	(void)input;
	//std::cout << input->MouseDown(0) << std::endl;
}

int	main(void)
{
	GLWindow* window = new GLWindow("#gl");
	Input* input = new Input("#body");
	(void)window;

	test_render(input);
	//emscripten_set_main_loop_arg(test_render, input, 0, 0);
}
