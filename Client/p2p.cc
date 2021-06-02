#include "p2p.h"

RS::P2PLIB::P2PLIB() {
    P2PLIB(1);
}

RS::P2PLIB::P2PLIB(int n){
    for(int i = 0; i < n; i++){
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