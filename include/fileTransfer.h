#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080

class fileTransfer { 
private:

    int serverFD, newSocket, valread, sock = 0, clientFD;
    sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

public:
    void setUpHostSocket(); // sets up socket, setsockopt, address params, binds and listens
    // returns -1 if something went wrong
    int setUpClientSocket();
    // also accept a new connection
    int getFile(); // download file
    
};