#pragma once

#include <chrono>

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
	std::chrono::time_point<std::chrono::system_clock> last_connect_time;

	Client();
};
