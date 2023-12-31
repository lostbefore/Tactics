/*Windows：
打开命令提示符（CMD）。
输入 ipconfig 并按回车。
查找 IPv4 地址，这就是你的计算机在局域网中的 IP 地址。*/
#include"../tcpSocket/tcpSocket.h"
#include<iostream>
int main()
{
	init_Socket();
	SOCKET serfd = createServerSocket();
	std::cout << "Wait for connection..." << std::endl;
	SOCKET clifd = accept(serfd, NULL, NULL);
	if (clifd != INVALID_SOCKET)
	{
		std::string recvbuf = receiveData(clifd);
		std::cout << "Received: " << recvbuf << std::endl;

		std::string sendbuf = "NIHAO!";
		sendData(clifd, sendbuf);
		std::cout << "Sent: " << sendbuf << std::endl;
	}
	closesocket(clifd);
	closesocket(serfd);
	close_Socket();
	return 0;
}
