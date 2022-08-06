#include "../include/fileTransfer.h"

void fileTransfer::setUpHostSocket(){
    if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(serverFD, (struct sockaddr*) &address, sizeof(address)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(serverFD, 3) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if((newSocket = accept(serverFD, (struct sockaddr*)&address, (socklen_t*)&addrlen)) == -1){
        perror("accept");
        exit(EXIT_FAILURE);
    }


}

int fileTransfer::setUpClientSocket(){
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("\nSocket creation error\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) == -1){
        printf("\nInvalid address/ Address not supported");
        return -1;
    }
    if ((clientFD = connect(sock, (sockaddr*)&address, sizeof(address))) == -1){
        printf("\nConnection failed \n");
        return -1;
    }

}