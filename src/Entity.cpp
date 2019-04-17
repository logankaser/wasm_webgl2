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

	// reset value prior to recalculate max entity size
	_max_size = 0;

	// Update any renderables with new values. Add renderable ids
	// to set of known_ids for use later with removing old renderables
	std::unordered_set<uint32_t> known_ids;
	for (auto& r : entity.renderable())
	{
		// setting _max_size to the maximum size of a renderable
		// stored in entity
		_max_size = std::max(_max_size, r.size());

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

	// smoothly move render pos towards actual position
	constexpr double diff = 0.3;
	_renderpos = _pos * (1 - diff) + _renderpos * diff;
}

void Entity::Render(float scale, float aspect, glm::vec2 cam_pos)
{
	float scale_sq = scale * scale;

	// calculate the dimensions of the box used to normalize coordinates
	glm::vec2 normalizing_box;
	if (aspect > 1)
		normalizing_box = glm::vec2(scale * aspect, scale);
	else
		normalizing_box = glm::vec2(scale, scale / aspect);

	// reduce the normalizing box size if it has too much area
	float box_area = normalizing_box.x * normalizing_box.y;
	if (box_area > scale_sq * _area_modifier)
		normalizing_box	*= box_area / scale_sq;

	// get the entity position in normalized device coordinates
	glm::vec2 normalized_pos = (cam_pos - _renderpos) / normalizing_box;

	// how much objects should be scaled
	glm::vec2 render_scale = glm::vec2(1.0) / normalizing_box;

	for (auto& r : _renderables)
	{
		r.second->Render(normalized_pos, _dir, render_scale);
	}
}
