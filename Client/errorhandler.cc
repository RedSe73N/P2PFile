#include "p2p.h"

#include <stdio.h>
#include <stdlib.h>

void RS::P2PLIB::errorFunc(std::string message) {
    fputs(message.c_str(), stderr);
    fputc('\n', stderr);
    exit(-1);
}