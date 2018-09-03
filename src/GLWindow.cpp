#include "GLWindow.hpp"

GLWindow::GLWindow(const char* canvas)
{
	EmscriptenWebGLContextAttributes attrs;
	emscripten_webgl_init_context_attributes(&attrs);
	attrs.depth = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 2;
	attrs.minorVersion = 0;

	_context = emscripten_webgl_create_context(canvas, &attrs);
	emscripten_webgl_make_context_current(_context);
}

GLWindow::~GLWindow()
{
	emscripten_webgl_destroy_context(_context);
}

float	GLWindow::Aspect()
{
	return _aspect;
}

void	GLWindow::SetRenderRectangle(float width, float height, glm::vec2 center)
{
	glEnable(GL_SCISSOR_TEST);

	int w, h;
	emscripten_webgl_get_drawing_buffer_size(_context, &w, &h);

	int x = w * (center.x + 1) / 2.0;
	int y = h * (center.y + 1) / 2.0;
	w = w * width / 2.0 + 0.5;
	h = h * height / 2.0 + 0.5;
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);

	_aspect = w / (float)h;
}

void	GLWindow::UnsetRenderRectangle()
{
	int w, h;
	emscripten_webgl_get_drawing_buffer_size(_context, &w, &h);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	glDisable(GL_SCISSOR_TEST);

	_aspect = w / (float)h;
}
