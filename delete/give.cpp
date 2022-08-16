#include "../include/fileTransfer.h"
#include <string>


int main(){

    fileTransfer client;

    client.setUpClientSocket();
    client.findSize("test2.txt");
    client.sendFileClient("test2.txt");
}