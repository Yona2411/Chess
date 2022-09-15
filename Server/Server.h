#pragma once
#include "Communicator.h"

class Server
{
private:
	Server(void);
	static Server* instance;

	Communicator* m_communicator;

public:
	/* Singletons should not be cloneable or assignable. */
	/////////////////////////////////////////////
	Server(Server& other) = delete;
	void operator=(const Server& other) = delete;
	/////////////////////////////////////////////

	static Server* get_instance(void);
	~Server(void);

	void run(void);
};
