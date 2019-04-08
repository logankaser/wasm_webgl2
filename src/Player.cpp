#include "Player.hpp"


Player::Player(const Input* input, uint64_t id)
{
	_input = input;
	_id = id;
}

Player::~Player()
{
}

game_protocol::Status Player::GetStatus() const
{
	game_protocol::Status status;
	status.set_player_id(_id);
	glm::vec2 mouse_pos = _input->MousePos();
	status.set_vel_x(mouse_pos.x);
	status.set_vel_y(mouse_pos.y);
	status.set_dir_x(mouse_pos.x);
	status.set_dir_y(mouse_pos.y);
	status.add_action(game_protocol::Action::GUN);
	return status;
}
