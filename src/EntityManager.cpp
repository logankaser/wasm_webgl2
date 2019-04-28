#include "EntityManager.hpp"

EntityManager::EntityManager()
{
	// negative time is invalid so can be used to signal no update
	// has taken place
	_base_server_time = -1;
}

void EntityManager::Update(const game_protocol::Update& update)
{
	// update server camera pos
	_server_camera_pos.x = update.cam_x();
	_server_camera_pos.y = update.cam_y();

	_camera_scale = update.cam_scale();

	// if first update...
	if (_base_server_time < 0)
	{
		_base_server_time = update.time();
		_timer.Reset();

		_camera_pos = _server_camera_pos;
	}

	_timer.Fix();
	double server_total = update.time() - _base_server_time;
	double server_offset = _timer.Total() - server_total;

	// loop over entities in update and either update their values
	// or add a new one if non existant.
	for (const auto& e : update.entity())
	{
		uint32_t id = e.id();
		if (_entities.count(id) == 0)
			_entities[id] = new Entity();
		_entities[id]->Update(e, server_offset);
	}
	// remove entities in remove field
	for (auto rm : update.remove())
		_entities.erase(rm);
}

void EntityManager::Frame()
{
	// smoothly move camera towards server_camera
	constexpr double dif = 0.99;
	_camera_pos = _server_camera_pos * (1 - dif) + _camera_pos * dif;

	_timer.Fix();
	for (auto& p : _entities)
		p.second->Frame(_timer.Delta());
}

void EntityManager::Render()
{
	for (auto& p : _entities)
	{
		p.second->Render(_camera_scale, 1, _camera_pos);
	}
}
