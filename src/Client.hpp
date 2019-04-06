#pragma once

#include "GLWindow.hpp"
#include "Input.hpp"
#include "Player.hpp"
#include "networking/Socket.hpp"

class	Client
{
	static const constexpr char* _window_target = "#gl";
	static const constexpr char* _input_target = "#body";

public:
	GLWindow window;
	Input input;
	Player player;
	Socket socket;

	Client();
};
