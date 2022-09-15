#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include <thread>

#include "SQLiteDB.h"

int main(void)
{
	// first initialize the singletons
	WSAInitializer* wsaInit = WSAInitializer::get_instance();
	Communicator* communicator = Communicator::get_instance();
	Server* server = Server::get_instance();
	IDatabase* db = SQLiteDB::get_instance();
	
	// run
	std::thread running(&Server::run, server);
	running.join();
	
	// delete the singletons at end of run
	delete db;
	delete server;
	delete communicator;
	delete wsaInit;

	system("pause");
	return 0;
}

