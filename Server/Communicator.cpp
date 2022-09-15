#include "Communicator.h"
#include <iostream>
#include <vector>

// initialize for static member
Communicator* Communicator::instance = nullptr;

Communicator::Communicator(void)
    :m_serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
    if (this->m_serverSocket == INVALID_SOCKET) 
        throw std::exception(__FUNCTION__ " - socket");
}

Communicator* Communicator::get_instance(void)
{
    if (instance == nullptr)
        instance = new Communicator();

    return instance;
}

Communicator::~Communicator(void)
{
    instance = nullptr;
    try
    {
        // the only use of the destructor should be for freeing 
        // resources that was allocated in the constructor
        closesocket(this->m_serverSocket);
    }
    catch (...) {}
}

void Communicator::startHandleRequests(void)
{
    struct sockaddr_in sa = { 0 };

    sa.sin_port = htons(PORT); // port that server will listen for
    sa.sin_family = AF_INET;   // must be AF_INET
    sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

    // Connects between the socket and the configuration (port and etc..)
    if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
        throw std::exception(__FUNCTION__ " - bind");

    // Start listening for incoming requests of clients
    if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
        throw std::exception(__FUNCTION__ " - listen");
    std::cout << "Listening on port " << PORT << std::endl;

    // try here to make sure when thread crash, bind and listen don't make error.
    try
    {
        while (true)
        {
            // the main thread is only accepting clients 
            // and add then to the list of handlers
            std::cout << "Waiting for client connection request" << std::endl;
            bindAndListen();
        }
    }
    catch (...) {}
}

void Communicator::bindAndListen(void)
{
    // this accepts the client and create a specific socket from server to this client
    // the process will not continue until a client connects to the server
    SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
    if (client_socket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__);

    std::cout << "Client accepted. Server and client can speak" << std::endl;

    // the function that handle the conversation with the client
    std::thread tr(&Communicator::handleNewClient, this, client_socket);
    tr.detach();
}


/************************************************\
*                                                *
* this function is the start for every client... *
*                                                *
\************************************************/
void Communicator::handleNewClient(SOCKET clientSocket)
{
    try
    {
        
        closesocket(clientSocket);
    }
    catch (const std::exception& e)
    {
        closesocket(clientSocket);
    }
}
