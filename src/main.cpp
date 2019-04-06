#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Client.hpp"
#include "networking/game_protocol.pb.h"

void main_loop(void* arg)
{
	Client* client = static_cast<Client*>(arg);

	client->socket.Update();
	if (client->socket.connected)
	{
		int socket = client->socket.GetSocket();
		static int count = 0;
		std::string msg = std::to_string(count);
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
			if (count % 60 == 0)
			{
				game_protocol::Update up;
				up.ParseFromArray(buff + 2, len);
				std::cout << up.time() << std::endl;
				for (auto entity : up.update()) {
					std::cout << entity.id() << std::endl;
				}
			}
		}
		++count;
	}

	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto v = client->input.MousePos();
	client->window.SetRenderRectangle(1, 1, v);
	client->player.Render(v);
}

int	main()
{
	Client* client = new Client();
	emscripten_set_main_loop_arg(main_loop, client, 0, 0);
}
