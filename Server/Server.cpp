#include "Server.h"
#include "Server.h"
#include "Server.h"
#include "Server.h"
#include "Server.h"

// initialize for static member
Server* Server::instance = nullptr;

Server::Server(void)
{
	this->m_communicator = Communicator::get_instance();
}

Server* Server::get_instance(void)
{
	if (instance == nullptr)
		instance = new Server();

	return instance;
}

Server::~Server(void)
{
	instance = nullptr;
}

void Server::run(void)
{
	std::string userInput;
	std::thread handleRequest(&Communicator::startHandleRequests, this->m_communicator);
	handleRequest.detach();

	while (userInput != "EXIT")
		std::cin >> userInput;
}
