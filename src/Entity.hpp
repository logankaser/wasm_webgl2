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

	// _renderpos and _pos may differ slightly when rubberbanding
	// _pos is the actual position
	glm::vec2 _renderpos;

	double _created;
	glm::vec2 _pos;
	glm::vec2 _vel;
	glm::vec2 _dir;
	std::string _name;
	std::string _chat;

	float _max_size;

	// used to make playing on different aspect ratios fair
	static constexpr const float _area_modifier = 0.7;

public:

	void Update(game_protocol::Entity, double server_offset);
	void Frame(double dt);
	void Render(float scale, float aspect, glm::vec2 cam_pos);
};
