#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include "graphic_core.hpp"


class	GLWindow
{
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE _context;
	float _aspect;
public:
	//! initialize and use a webGL context
	GLWindow(const char* canvas);
	
	//! destroy the webGL context
	~GLWindow();

	//! aspect ratio of current render rectangle
	float	Aspect();

	//! sets the render rectangle based on normalized device coordinates
	void	SetRenderRectangle(float width, float height, glm::vec2 center);

	//! resets render rectangle to cover the entire canvas
	void	UnsetRenderRectangle();
};
