/*Windows��
��������ʾ����CMD����
���� ipconfig �����س���
���� IPv4 ��ַ���������ļ�����ھ������е� IP ��ַ��*/
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
