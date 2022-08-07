#include "../include/fileTransfer.h"


int main(){

    fileTransfer client;

    client.setUpClientSocket();
    client.findSize();
    client.sendFileClient();
}