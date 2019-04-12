#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <unordered_map>

#include "graphic_core.hpp"
#include "networking/game_protocol.pb.h"
#include "Renderable.hpp"

class	Entity
{
	std::unordered_map<uint32_t, Renderable*> _renderables;

	double _created;
	glm::vec2 _pos;
	glm::vec2 _vel;
	glm::vec2 _dir;
	std::string _name;
	std::string _chat;

public:

	void Update(game_protocol::Entity, double server_offset);
	void Render();
};
