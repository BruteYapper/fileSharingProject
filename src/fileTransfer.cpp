#include "../include/fileTransfer.h"
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cmath> // temp include

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

    // std::ofstream file;
    // // std::string temp {buffer, std::ios::app};
    // char fileName[100] = {0};
    // char fileLength[500] = {0};


    // if(!file){
    //     std::cout << "Error in creating file!!";
    //     return 0;
    // }
    // // unpacks first packet (gets name and file size)
    // std::cout << "started reading" << std::endl;
    // read(newSocket, numBuffer, 1023);


    // std::cout << numBuffer << std::endl;


    // // gets name of file
    // for (int j, i = 0; numBuffer[i] != ')'; i++){
    //     if (numBuffer[i] == '(')
    //         continue;
        
    //     fileName[i-1] = numBuffer[i];
    // }    
    
    
    // // gets size of file
    // bool readyForLength = false;
    // for (int j = 0, i = 0; numBuffer[i] != ']'; i++){
    //     if (readyForLength){
    //         fileLength[j] = numBuffer[i];
    //         j++;

    //     }

    //     if (numBuffer[i] == '[')
    //         readyForLength = true;
    // }
    

    // file.open((fileName), std::ios::out); 
    
    // fileSizeInBytes = atoi(fileLength);



    // std::cout << std::endl << "buffer After" << std::endl;
    // // std::cout << buffer << std::endl;


    

    

    // fileSizeInBytes = fileSizeInBytes / 1024;
    // // std::cout << buffer << std::endl;
    // memset(numBuffer, 0, sizeof(numBuffer));
    // // std::cout << buffer << std::endl;
    // for (int i = 0; i != (fileSizeInBytes+1); i++){ // this works because arrays are just pointers to the beginning of the array

    //     valread = read(newSocket, msgBuffer, 1024);

    //     // if (i == (fileSizeInBytes)){
    //     //     std::cout << "msgBuffer" << "\n"; 
    //     //     // file << "=================================================" << std::endl;
    //     // }

    //     file << msgBuffer;
        
    // }

   
    //Read Picture Size
    printf("Reading Picture Size\n");
    int size;
    int nameSize;
    read(newSocket, &size, sizeof(int));
    printf("%i is the size of the file", size);
    //Read Picture Byte Array
    printf("Reading Picture Byte Array\n");

    //Convert it Back into Picture
    printf("Converting Byte Array to Picture\n");
    read(newSocket, &nameSize, sizeof(int));
    printf("%i\n", nameSize);
    char p_array[1000];
    char fileName[nameSize];
    read(newSocket, fileName, nameSize*8);
    
    FILE *image;
    image = fopen(fileName, "w");
    // bzero(p_array, sizeof(p_array));



    do{
        if(size > 1000){ // this is the main section that sends in packets of 1000
            read(newSocket, p_array, sizeof(p_array));
            fwrite(p_array, 1, sizeof(p_array), image);
            // bzero(p_array, sizeof(p_array));
            size -= 1000;
        }
        else{ // once there is less then 1000 it makes a custom amount and since the client keeps track of this number they are both expecting this number
            char newReadBuffer[size];
            read(newSocket, newReadBuffer, sizeof(newReadBuffer));
            fwrite(newReadBuffer, 1, sizeof(newReadBuffer), image);
            size -= size;
        }
    } while (size > 0);


    
    close(sock);
    shutdown(serverFD, SHUT_RDWR);

    return 0;


}

int fileTransfer::sendFileClient(const char *fileName){
    
    // std::ifstream inFile {fileName, std::ios::in}; 
    // std::string info;

    // if(!inFile){
    //     std::cerr << "There was an error\n" << std::endl;
    //     return -1;
    // }
    // // temp will be formated so the name of the file will be in () and the size will be [] the rest will be filled with '1'
    // std::string temp = "";
    // temp.append("(");
    // temp.append(fileName);
    // temp.append(")");
    
    // temp.append("[");    
    // temp.append(std::to_string(fileSizeInBytes));
    // temp.append("]");
    



    
    // int tempInt = (1023 - temp.size());
    // for (int i = 0; i < tempInt; i++){
    //     temp.append("1");
    // }

    





    // send(sock, temp.c_str(), strlen(temp.c_str()), 0); // sends the number of bytes the file is as a string

    // fileSizeInBytes = fileSizeInBytes / 1024;
    // for (int i = 0; i != (fileSizeInBytes+1); i++){ 
    //     for (size_t i = 0; i != 1023; i++)
    //     {
    //         if (inFile.peek() != EOF)
    //             info += inFile.get();
    //         else
    //             info += ' ';
    //     }
    //     send(sock, info.c_str(), strlen(info.c_str()), 0);
    //     // std::cout << info << std::endl;
    //     // std::cout << "==========" << std::endl;

    //     info.clear();
    // }



    printf("Getting Picture Size\n");
    FILE *picture;
    picture = fopen(fileName, "r");
    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);

    int sendSize = 1000;

    //Send Picture Size
    printf("Sending Picture Size\n");
    send(sock, &size, sizeof(size), 0);

    int sizeOfFileName = strlen(fileName);

    send(sock, &sizeOfFileName, sizeof(int), 0);

    send(sock, fileName, sizeOfFileName*8, 0);

    //Send Picture as Byte Array
    printf("Sending Picture as Byte Array\n");
    char send_buffer[sendSize];
    do {
        if(size > sendSize){
            fread(send_buffer, 1, sizeof(send_buffer), picture);
            write(sock, send_buffer, sizeof(send_buffer));
            bzero(send_buffer, sizeof(send_buffer));
            size -= sendSize;
            printf("Size: %i\n", size);
        }
        else{
            char newSendBuffer[size];
            fread(newSendBuffer, 1, sizeof(newSendBuffer), picture);
            write(sock, newSendBuffer, sizeof(newSendBuffer));
            bzero(newSendBuffer, sizeof(newSendBuffer)); // I know this isn't required
            size -= size;
        }
    } while(size > 0);



    // send(sock, endMessage, strlen(endMessage), 0);
    std::cout << "ended sending the file" << std::endl;
    close(sock);
    fclose(picture);
    return 0;

}

// void fileTransfer::findSize(const char *fileName){
//     // FILE *fp = fopen(fileName, "rb");
//     // std::cout << "made it here\n";
//     // fseek(fp, 0, SEEK_END);
//     // fileSizeInBytes = ftell(fp);
//     // fclose(fp);

// }


