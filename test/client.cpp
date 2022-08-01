#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(){
    int sock = 0, valread, clientFD;
    sockaddr_in servAddr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0){
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }
    if ((clientFD = connect(sock, (sockaddr*)&servAddr, sizeof(servAddr))) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
    
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // closing the connected socket
    close(clientFD);
    return 0;
}