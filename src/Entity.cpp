#include "Entity.hpp"

void Entity::Update(game_protocol::Entity entity, double server_offset)
{
	_created = entity.created();
	_pos = glm::vec2(entity.pos_x(), entity.pos_y());
	_vel = glm::vec2(entity.vel_x(), entity.vel_y());
	_dir = glm::vec2(entity.dir_x(), entity.vel_y());
	_name = entity.name();
	_chat = entity.chat();

	// Extrapolate position using server_offset time
	_pos += _vel * server_offset;

	// Update any renderables with new values. Add renderable ids
	// to set of known_ids for use later with removing old renderables
	std::unordered_set<uint32_t> known_ids;
	for (auto& r : entity.renderable())
	{
		uint32_t id = r.id();
		known_ids.emplace(id);

		if (_renderables.count(id))
			_renderables[id]->Update(r);
		else
			_renderables[id] = new Renderable(r);
	}
	// remove all entries from the map with id not in known_ids
	std::vector<uint32_t> delete_ids;
	for (auto& pair : _renderables)
	{
		if (known_ids.count(pair.first) == 0)
		{
			delete pair.second;
			delete_ids.push_back(pair.first);
		}
	}
	for (auto id : delete_ids)
		_renderables.erase(id);
}

void Entity::Frame(double dt)
{
	_pos += _vel * dt;
	double diff = 0.3;
	_renderpos = _pos * (1 - diff) + _renderpos * diff;
}

void Entity::Render()
{
	for (auto& r : _renderables)
	{
		r.second->Render(_renderpos, _dir);
		r.second->Render(_pos, _dir);
	}
}
