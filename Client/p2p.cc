#include "p2p.h"

RS::P2PLIB::P2PLIB() {
    P2PLIB(1);
}

RS::P2PLIB::P2PLIB(int n){
    for(int i = 0; i < (threadNum=n); i++){
        Worker __worker = {
            .client = std::thread(clientFunction),
            .server = std::thread(serverFunction)
        };
        workers.push_back(__worker);
    }
}

RS::P2PLIB::~P2PLIB(){
    //TODO
}

void RS::P2PLIB::startAll(){
    start(threadNum);
}

void RS::P2PLIB::start(int n){
    #define o(x) \
        x.client.join(); \
        x.server.join();
    for(int i = 0; i < n; i+=2){
        o(workers[i]);
    }
    #undef o
}