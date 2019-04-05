#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include "graphic_core.hpp"


class	GLWindow
{
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE _context;
	float _aspect;
	int _width;
	int _height;

	bool _renderRectangleSet;
	float _renderRectangleWidth;
	float _renderRectangleHeight;
	glm::vec2 _renderRectangleCenter;

	static EM_BOOL onResize(int, const EmscriptenUiEvent*, void*);

public:
	//! initialize and use a webGL context
	GLWindow(const char* canvas);

	//! destroy the webGL context
	~GLWindow();

	//! aspect ratio of current render rectangle
	float	Aspect() const;

	//! width of window in pixels
	int	Width() const;

	//! height of window in pixels
	int	Height() const;

	//! sets the render rectangle based on normalized device coordinates
	/*!
	`center` is the center of the rectangle. A rectangle filling the whole
	screen has `center` of (0, 0) and `width` and `height` == 2
	*/
	void	SetRenderRectangle(float width, float height, glm::vec2 center);

	//! resets render rectangle to cover the entire canvas
	void	UnsetRenderRectangle();
};
