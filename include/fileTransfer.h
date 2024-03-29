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
    // check if the client is still connected to host
    int error, retval;
    socklen_t len; 
    long int fileSizeInBytes;


public:
    void setUpHostSocket(); // hosts the file
    // sets up socket, setsockopt, address params, binds and listens
    // returns -1 if something went wrong
    int setUpClientSocket(); // connects to the host using ipv4
    // also accept a new connection
    int setUpClientSocket(char* IP);

    int getFileHost(); // download file

    int sendFileClient(const char *fileName);  // send file to client


    
};