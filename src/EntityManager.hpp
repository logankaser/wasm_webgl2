#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <unordered_map>

#include "graphic_core.hpp"
#include "networking/game_protocol.pb.h"
#include "Entity.hpp"

class	EntityManager
{
	std::unordered_map<uint32_t, Entity*> _entities;

public:

	void Update(const game_protocol::Update&);
	void Render();
};
