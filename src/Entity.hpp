#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>

#include "graphic_core.hpp"

class	Entity
{

protected:
	void _move();

public:
	Entity();
	~Entity();

	void Update();
};
