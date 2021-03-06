#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <chrono>

#include "Client.hpp"
#include "networking/game_protocol.pb.h"
#include "config.hpp"

extern "C" void __set_hp(int hp);

void main_loop(void* arg)
{
	Client* client = static_cast<Client*>(arg);
	static int count;
	client->socket.Update();
	if (client->socket.connected)
	{
		client->last_connect_time = std::chrono::system_clock::now();
		int socket = client->socket.GetSocket();
		auto status = client->player.GetStatus();
		std::string msg;
		status.AppendToString(&msg);
		send(socket, msg.data(), msg.size(), 0);
		uint8_t buff[4096];
		int ret = recv(socket, &buff, 4096, 0);
		if (ret != -1)
		{
			uint16_t len;
			std::memcpy(&len, buff, 2);
			if (len > 4096)
				std::cerr << "Update packet too large" << std::endl;
			if (len + 2 != ret)
				std::cerr << "Multi recv packet" << std::endl;
			game_protocol::Update up;
			up.ParseFromArray(buff + 2, len);
			client->entity_manager.Update(up);
		}
		++count;
	}
	else
	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = now - client->last_connect_time;
		if (diff.count() > 1.0)
		{
			if (client->socket.Connect(SERVER_IP, 3000) != Socket::success)
				std::cerr << "Error connecting to socket" << std::endl;
			client->last_connect_time = now;
		}
	}
	client->entity_manager.Frame();

	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	client->entity_manager.Render();
}

int	main()
{
	Client* client = new Client();
	emscripten_set_main_loop_arg(main_loop, client, 0, 0);
}
