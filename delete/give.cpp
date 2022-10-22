#include "../include/fileTransfer.h"
#include <string>


int main(){

    fileTransfer client;

    client.setUpClientSocket();
    // client.findSize("lemon.png");
    client.sendFileClient("lemon.png");
}