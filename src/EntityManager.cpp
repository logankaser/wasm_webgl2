#include "EntityManager.hpp"

EntityManager::EntityManager()
{
	// negative time is invalid so can be used to signal no update
	// has taken place
	_base_server_time = -1;
}

void EntityManager::Update(const game_protocol::Update& update)
{
	if (_base_server_time < 0)
	{
		_base_server_time = update.time();
		_timer.Reset();
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
	_timer.Fix();
	for (auto& p : _entities)
		p.second->Frame(_timer.Delta());
}

void EntityManager::Render()
{
	for (auto& p : _entities)
		p.second->Render();
}
