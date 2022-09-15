#pragma once
#include <iostream>
#include <exception>
#include <thread>
#include <map>
#include <time.h>
#include <WinSock2.h>
#include <Windows.h>

#define PORT 8080

class Communicator
{
private:
	Communicator(void);
	static Communicator* instance;

	SOCKET m_serverSocket;
	void bindAndListen(void);
	void handleNewClient(SOCKET clientSocket);

public:
	/* Singletons should not be cloneable or assignable. */
	///////////////////////////////////////////////////
	Communicator(Communicator& other) = delete;
	void operator=(const Communicator& other) = delete;
	///////////////////////////////////////////////////

	static Communicator* get_instance(void);
	~Communicator(void);

	void startHandleRequests(void);
};
