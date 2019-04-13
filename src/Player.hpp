#pragma once

#include "networking/game_protocol.pb.h"
#include "Input.hpp"

//! An abstraction over Input that converts raw input into actions
class	Player
{
	const Input* _input;
	uint64_t _id;
public:
	Player(const Input*, uint64_t id);
	~Player();

	game_protocol::Status GetStatus() const;
};
