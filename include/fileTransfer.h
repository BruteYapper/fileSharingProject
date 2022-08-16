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
    char numBuffer[1024] = {0};
    char msgBuffer[1024] = {0};
    // check if the client is still connected to host
    int error, retval;
    socklen_t len; 
    long int fileSizeInBytes;


public:
    void setUpHostSocket(); // sets up socket, setsockopt, address params, binds and listens
    // returns -1 if something went wrong
    int setUpClientSocket();
    // also accept a new connection
    int getFileHost(); // download file

    int sendFileClient(const char *fileName);

    void findSize(const char *fileName);

    
};