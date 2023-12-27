#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#include<WinSock2.h>
#include<stdbool.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#define PORT 8888
bool init_Socket();
bool close_Socket();
SOCKET createServerSocket();
SOCKET createClientSocket(const char* ip);
bool sendData(SOCKET fd, const std::string& data);
std::string receiveData(SOCKET fd);
#endif#pragma once
