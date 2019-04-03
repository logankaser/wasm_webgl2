#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <string>
#include <unordered_map>

#include "graphic_core.hpp"
#include "Rectangle.hpp"
#include "TextureFactory.hpp"

class	Player
{
	Texture _texture;

public:
	Player();
	~Player();

	void Render();
};
