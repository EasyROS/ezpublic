#include "Server.hpp"
#include <EZOutput.hpp>

void *call(char * str){
    cout << str << endl;
    EZServer::sendToClient("succ");
}

Server::Server(){
    out::listen(call);
}

void Server::test() {
    cout << "test" << endl;
}