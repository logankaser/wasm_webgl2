#include "GLWindow.hpp"
#include <iostream>

EM_BOOL GLWindow::onResize(int, const EmscriptenUiEvent* uiEvent, void* data)
{
	GLWindow* window = (GLWindow*)data;

	window->_width = uiEvent->windowInnerWidth;
	window->_height = uiEvent->windowInnerHeight;
	window->_aspect = float(window->_width) / float(window->_height);

	if (window->_renderRectangleSet)
	{
		window->SetRenderRectangle(
			window->_renderRectangleWidth,
			window->_renderRectangleHeight,
			window->_renderRectangleCenter
		);
	}
	else
		window->UnsetRenderRectangle();

	return false;
}

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

	emscripten_get_canvas_element_size(canvas, &_width, &_height);
	_aspect = float(_width) / float(_height);

	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,
		this, false, onResize);

	_renderRectangleSet = false;
}

GLWindow::~GLWindow()
{
	emscripten_webgl_destroy_context(_context);
}

float	GLWindow::Aspect() const
{
	return _aspect;
}

int	GLWindow::Width() const
{
	return _width;
}

int	GLWindow::Height() const
{
	return _height;
}

void	GLWindow::SetRenderRectangle(float width, float height, glm::vec2 center)
{
	glEnable(GL_SCISSOR_TEST);

	int w, h;
	emscripten_webgl_get_drawing_buffer_size(_context, &w, &h);

	//std::cout << center.x << " " << center.y << std::endl;
	float x = w * (center.x - width / 2.0 + 1) / 2.0;
	float y = h * (center.y - height / 2.0 + 1) / 2.0;

	w = w * width / 2.0 + 0.5;
	h = h * height / 2.0 + 0.5;

	std::cout << x << " " << y << " " << w << " " << h << std::endl;

	glViewport(x, y, w, h);
	glScissor(x, y, w, h);

	_aspect = w / (float)h;

	_renderRectangleWidth = width;
	_renderRectangleHeight = height;
	_renderRectangleCenter = center;
	_renderRectangleSet = true;
}

void	GLWindow::UnsetRenderRectangle()
{
	int w, h;
	emscripten_webgl_get_drawing_buffer_size(_context, &w, &h);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	glDisable(GL_SCISSOR_TEST);

	_aspect = w / (float)h;
	_renderRectangleSet = false;
}
