#include "Entity.hpp"

void Entity::_move(double dt)
{
	_pos += dt * _vel;
}


void Entity::Update(
	double dt,
	glm::vec2 vel,
	glm::vec2 dir,
	glm::vec2 pos)
{
	_dir = dir;
}
