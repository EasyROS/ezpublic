
#include "Server.h"


void *call(char * str){
    cout << str << endl;

    Server *S;
    S->CommandResolve(str);


    EZServer::sendToClient("succ");
}

Server::Server(){
    out::listen(call);
}

void Server::CommandResolve(string cmd) {
    vector<string> comm = EZTools::format(cmd, ' ');

}