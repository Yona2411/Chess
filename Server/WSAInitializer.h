#pragma once

#include <WinSock2.h>
#include <Windows.h>


class WSAInitializer
{
private:
	WSAInitializer(void);
	static WSAInitializer* instance;
public:
	/* Singletons should not be cloneable or assignable. */
	///////////////////////////////////////////////
	WSAInitializer(WSAInitializer& other) = delete;
	void operator=(const WSAInitializer& other) = delete;
	///////////////////////////////////////////////

	static WSAInitializer* get_instance(void);
	~WSAInitializer();
};

