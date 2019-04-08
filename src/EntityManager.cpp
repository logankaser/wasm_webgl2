#include "EntityManager.hpp"

void EntityManager::Update(const game_protocol::Update& update)
{
	// loop over entities in update and either update their values
	// or add a new one if non existant.
	for (const auto& e : update.entity())
	{
		uint32_t id = e.id();
		if (_entities.count(id) == 0)
			_entities[id] = new Entity();
		_entities[id]->Update(e);
	}
	// remove entities in remove field
	for (auto rm : update.remove())
		_entities.erase(rm);
}

void EntityManager::Render()
{
	for (auto& p : _entities)
		p.second->Render();
}
