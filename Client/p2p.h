#include <iostream>
#include <thread>
#include <vector>
#include <arpa/inet.h>

uint16_t operator""HS(unsigned long long a){
    return htons(a);
}

uint32_t operator""HL(unsigned long long a){
    return htonl(a);
}

struct Worker{
    std::thread client;
    std::thread server;
};

namespace RS {

    class P2PLIB {
    private:
        int threadNum = 0;
        std::vector<Worker> workers; // thread worker
        void errorFunc(std::string message); // error Message
        void serverFunction();
        void clientFunction();
    public:
        ~P2PLIB();
        P2PLIB();
        P2PLIB(int n);
        void startAll();
        void start(int n);
    };
}