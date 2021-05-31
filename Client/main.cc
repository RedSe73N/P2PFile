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

void errorFunc(char* message);

void serverFunction(std::string port){
    int serverFD;
    int clntFD;
    char *message = "Hello World";
    if((serverFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
        errorFunc("socket error");
    
    #define o(X) memset(&X, 0, sizeof(X));
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    socklen_t clntAddrSize;
    o(servAddr);
    o(clntAddr);
    #undef o

    servAddr.sin_family = AF_INET; //IPv4
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(10100);

    if(bind(serverFD, (struct sockaddr*)&servAddr, sizeof(servAddr))==-1)
        errorFunc("bind() error");
    
    if((listen(serverFD, 5)) == -1)
        errorFunc("listen() error");

    clntFD = accept(serverFD, (struct sockaddr*)&clntAddr, &clntAddrSize);
    if(clntFD == -1)
        errorFunc("accept() error");
    
    write(clntFD, message, sizeof(message));

    close(clntFD);
    close(serverFD);
    std::cout << "Server done\n";
}

void clientFunction(void){
    std::string serverPort;
    int socketFD; //socket
    int fd; //file descriptor
    struct sockaddr_in servAddr; //server address
    char message[256] = {0,};
    socketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketFD == -1)
        errorFunc("client socket() error");
    
    std::cout << "Client Server Port: ";
    std::cin >> serverPort;

    memset(&servAddr, 0, sizeof(servAddr));
    
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(serverPort.c_str()));
    
    if(connect(socketFD, (struct sockaddr*)&servAddr, sizeof(servAddr))==-1)
        errorFunc("connect() error!");
    
    if(read(socketFD, message, sizeof(message)-1)==-1)
        errorFunc("read() error!");
    
    std::cout << "message: " <<  message << std::endl;
    close(socketFD);
}

int main(int argc, char** argv){
    std::string input;
    std::cout << "RedSe73N P2P\n";
    std::cout << "\nServer Port Number: ";
    std::cin >> input;
    std::thread serverThread(serverFunction, input);
    std::thread clientThread(clientFunction);
    serverThread.join();
    if(std::string(argv[1])=="-c") clientThread.join();
}

void errorFunc(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(-1);
}