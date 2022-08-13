#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
// tutoral: https://www.geeksforgeeks.org/socket-programming-cc/
int main(){
    int serverFd, newSocket, valread;

    sockaddr_in address;  // sockaddr_in is for IPv4 while sockaddr is for IPv4 and IPv6
    int opt = 1;
    int addrlen  = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server!";
    

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(serverFd, (struct sockaddr*) &address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(serverFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);

    }

    valread = read(newSocket, buffer, 1024);
    printf("%s\n", buffer);
    send(newSocket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closeing the connected socket
    close(newSocket);
    // closing the listening socket
    shutdown(serverFd, SHUT_RDWR);

    return 0;
}
