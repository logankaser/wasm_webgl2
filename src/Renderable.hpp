#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include "graphic_core.hpp"
#include "networking/game_protocol.pb.h"
#include "TextureFactory.hpp"
#include "Rectangle.hpp"

class	Renderable
{
	GLuint _texture;
	uint32_t _color;
	float _size;
public:
	Renderable(const game_protocol::Renderable&);

	void Update(const game_protocol::Renderable&);
	void Render(glm::vec2 pos, glm::vec2 dir);
};
