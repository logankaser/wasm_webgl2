#pragma once

#include <string>
#include <cstdint>
#include <poll.h>

class Socket
{
	struct pollfd _socket;
public:
	bool connected;
	enum SocketConnect
	{
		success = 0,
		error_socket = 1, // Failed to create socket
		error_host = 2, // Failed to parse host string
		error_connect = 3 // Failed to connect to host
	};
	Socket();
	SocketConnect Connect(const std::string& host, int port);
	void Update();
	int GetSocket();
};
