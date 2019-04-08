#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#include "Socket.hpp"

Socket::Socket() :
_socket((struct pollfd){-1, POLLIN | POLLOUT, 0}),
connected(false)
{}

Socket::SocketConnect Socket::Connect(const std::string& host, int port)
{
	if (_socket.fd != -1)
		close(_socket.fd);
	_socket.fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket.fd == -1) {
		return error_socket;
	}
	fcntl(_socket.fd, F_SETFL, O_NONBLOCK);

	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (inet_pton(AF_INET, host.data(), &addr.sin_addr) != 1) {
		return error_host;
	}

	const int res = connect(_socket.fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof addr);
	if (res == -1 && !(errno == EINPROGRESS || errno == EWOULDBLOCK || errno == EISCONN)) {
		return error_connect;
	}

	return success;
}

void Socket::Update()
{
	_socket.revents = 0;
	int ret = poll(&_socket, 1, 0);
	if (ret < 0 || _socket.revents & (POLLERR | POLLHUP | POLLPRI))
		connected = false;
	else if (_socket.revents & (POLLIN | POLLOUT))
		connected = true;
}

int Socket::GetSocket()
{
	return _socket.fd;
}