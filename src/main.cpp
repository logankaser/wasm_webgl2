#include <iostream>
#include <vector>
#include <cstring>
#include <stdint.h>

#include "Client.hpp"


void main_loop(void* arg)
{
	glClearColor(0.5, 0.1, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Client* client = static_cast<Client*>(arg);

	auto v = client->input.MousePos();
	client->window.SetRenderRectangle(1, 1, v);
	client->player.Render(v);
}

int	main()
{
	Client* client = new Client();
	emscripten_set_main_loop_arg(main_loop, client, 0, 0);
}
