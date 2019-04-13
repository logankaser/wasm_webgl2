#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <unordered_map>

#include "graphic_core.hpp"
#include "networking/game_protocol.pb.h"
#include "Entity.hpp"
#include "Time.hpp"

class	EntityManager
{
	std::unordered_map<uint32_t, Entity*> _entities;
	double _base_server_time;
	Time _timer;

public:
	EntityManager();

	void Update(const game_protocol::Update&);
	void Frame();
	void Render();
};
