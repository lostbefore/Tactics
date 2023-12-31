#include"tcpsocket.h"
#include <WS2tcpip.h>
bool init_Socket()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		return false;
	return true;
}
bool close_Socket()
{
	if (WSACleanup() != 0)
		return false;
	return true;
}
SOCKET createServerSocket()
{
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
		return INVALID_SOCKET;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
		return INVALID_SOCKET;
	listen(fd, 10);
	return fd;
}
SOCKET createClientSocket(const char* ip)
{
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
		return INVALID_SOCKET;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_pton(AF_INET, ip, &addr.sin_addr);
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
		return INVALID_SOCKET;
	return fd;
}
bool sendData(SOCKET fd, const std::string& data)
{
	int result = send(fd, data.c_str(), data.size(), 0);
	return result != SOCKET_ERROR;
}
std::string receiveData(SOCKET fd)
{
	char buffer[1024] = { 0 };
	int bytesRead = recv(fd, buffer, sizeof(buffer), 0);
	if (bytesRead > 0)
		return std::string(buffer, bytesRead);
	return "";
}
