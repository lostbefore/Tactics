#include"../tcpSocket/tcpSocket.h"
#include<iostream>
int main()
{
	init_Socket();
	SOCKET fd = createClientSocket("127.0.0.1");
	std::string sendbuf = "HELLO";
	if (sendData(fd, sendbuf))
	{
		std::cout << "Sent: " << sendbuf << std::endl;

		std::string recvbuf = receiveData(fd);
		std::cout << "Received: " << recvbuf << std::endl;
	}
	getchar();
	closesocket(fd);
	close_Socket();
	return 0;
}
