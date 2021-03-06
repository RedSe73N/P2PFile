#include "p2p.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <sys/types.h>
#include <fcntl.h>

void RS::P2PLIB::serverFunction(){
    int serverFD;
    int clntFD;
    int fileFD;
    char data[256] = { 0, };
    ssize_t fileSize=0;

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
    
    if(read(clntFD, data, sizeof(data)-1) == -1)
        errorFunc("Read Error");
    
    if((fileFD = open(data, O_RDONLY))==-1)
        errorFunc("File Open error");
    
    while((fileSize=read(fileFD, data, sizeof(data)))!=0){
        if(fileSize == -1) break;
        write(clntFD, data, fileSize);
    }

    close(fileFD);
    close(clntFD);
    close(serverFD);
    std::cout << "Server done\n";
}
