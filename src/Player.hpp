#pragma once

#include "networking/game_protocol.pb.h"
#include "Input.hpp"

//! An abstraction over Input that converts raw input into actions
class	Player
{
	const Input* _input;
public:
	Player(const Input*);
	~Player();

	game_protocol::Status GetStatus() const;
};
