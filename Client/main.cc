#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "p2p.h"

int main(int argc, char** argv){
    RS::P2PLIB P2P;
}

void errorFunc(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(-1);
}