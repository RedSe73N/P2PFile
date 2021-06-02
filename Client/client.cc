#include "p2p.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <sys/types.h>
#include <fcntl.h>

void RS::P2PLIB::clientFunction() {
    std::string serverPort;
    std::string fileName;

    int socketFD; //socket
    int fd; //file descriptor
    struct sockaddr_in servAddr; //server address
    socketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketFD == -1)
        errorFunc("client socket() error");
    
    std::cout << "Client Server Port: ";
    std::cin >> serverPort;

    std::cout << "File name: ";
    std::cin >> fileName;

    open(fileName.c_str(), O_WRONLY | O_CREAT);

    memset(&servAddr, 0, sizeof(servAddr));
    
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(serverPort.c_str()));
    
    if(connect(socketFD, (struct sockaddr*)&servAddr, sizeof(servAddr))==-1)
        errorFunc("connect() error!");
    
    write(socketFD, fileName.c_str(), fileName.size());

    close(socketFD);
}