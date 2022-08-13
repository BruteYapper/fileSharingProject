#include "../include/fileTransfer.h"
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <stdlib.h>

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
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }
    if ((clientFD = connect(sock, (sockaddr*)&address, sizeof(address))) == -1){
        printf("\nConnection failed \n");
        return -1;
    }


    return 1;
}



int fileTransfer::getFileHost(){

    std::ofstream file;
    // std::string temp {buffer, std::ios::app};
    file.open(("test.txt"), std::ios::out);


    if(!file){
        std::cout << "Error in creating file!!";
        return 0;
    }
    // reads the number of chars in the file that is being sent
    std::cout << "started reading" << std::endl;
    read(newSocket, numBuffer, 1024);
    std::cout << "done first read:\n" << numBuffer << std::endl;

    fileSizeInBytes = atoi(numBuffer);



    std::cout << std::endl << "buffer After" << std::endl;
    // std::cout << buffer << std::endl;


    

    

    fileSizeInBytes = fileSizeInBytes / 1024;
    // std::cout << buffer << std::endl;
    memset(numBuffer, 0, sizeof(numBuffer));
    // std::cout << buffer << std::endl;
    for (int i = 0; i != (fileSizeInBytes+1); i++){ // this works because arrays are just pointers to the beginning of the array

        valread = read(newSocket, msgBuffer, 1024);

        // if (i == (fileSizeInBytes)){
        //     std::cout << "msgBuffer" << "\n"; 
        //     // file << "=================================================" << std::endl;
        // }

        file << msgBuffer;
        
    }


    file.close();
    close(sock);
    shutdown(serverFD, SHUT_RDWR);

    return 0;


}

int fileTransfer::sendFileClient(){
    
    std::ifstream inFile {"test.txt", std::ios::in}; 
    std::string info;

    if(!inFile){
        std::cerr << "There was an error\n" << std::endl;
        return -1;
    }

    std::string temp = std::to_string(fileSizeInBytes);
    
    temp.append(".");


    for (int i = 0; i != (1023 - temp.size()); i++){
        temp.append("1");
    }

    
    std::cout << temp << std::endl;

    send(sock, temp.c_str(), strlen(std::to_string(fileSizeInBytes).c_str()), 0); // sends the number of bytes the file is as a string

    fileSizeInBytes = fileSizeInBytes / 1024;
    for (int i = 0; i != (fileSizeInBytes+1); i++){ 
        for (size_t i = 0; i != 1023; i++)
        {
            if (inFile.peek() != EOF)
                info += inFile.get();
            else
                info += ' ';
        }
        send(sock, info.c_str(), strlen(info.c_str()), 0);
        std::cout << info << std::endl;
        std::cout << "==========" << std::endl;

        info.clear();
    }


    // send(sock, endMessage, strlen(endMessage), 0);
    std::cout << "ended sending the file" << std::endl;
    close(sock);
    return 0;

}

void fileTransfer::findSize(){
    FILE *fp = fopen("test.txt", "rb");
    fseek(fp, 0, SEEK_END);
    fileSizeInBytes = ftell(fp);
    fclose(fp);

}