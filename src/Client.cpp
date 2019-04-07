#include "Client.hpp"

Client::Client() :
window(_window_target),
input(_input_target, &window),
player(&input)
{
	if (socket.Connect("127.0.0.1", 3000) != Socket::success)
		std::cerr << "Error connecting to websocket" << std::endl;
}
