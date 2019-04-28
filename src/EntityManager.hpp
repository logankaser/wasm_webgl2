#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>
#include <unordered_map>

#include "graphic_core.hpp"
#include "networking/game_protocol.pb.h"
#include "Entity.hpp"
#include "Time.hpp"
#include "Background.hpp"
#include "GLWindow.hpp"

class	EntityManager
{
	std::unordered_map<uint32_t, Entity*> _entities;
	double _base_server_time;
	Time _timer;

	// the position of the camera according to the server
	glm::vec2 _server_camera_pos;

	// the position of camera used for game logic (smoothly follows
	// the server camera)
	glm::vec2 _camera_pos;

	// the viewing rectangle of the camera
	float _camera_scale;
	
	Background* _background;
	
	// for getting aspect ratio
	const GLWindow* _window;

public:
	EntityManager(const GLWindow*);

	void Update(const game_protocol::Update&);
	void Frame();
	void Render();
};
