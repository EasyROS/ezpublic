#include "Server.h"

void *call(char * str){
    cout << str << endl;

    Server *S;
    S->CommandResolve(str);


    EZServer::sendToClient("succ");
}

EZCommand *LS = new EZCommand();
EZCommand *CD = new EZCommand();


Server::Server(){
    //LS->Command->Add()
    this->pRoot = new directory("root");
    this->CMD;

    out::listen(call);
}

void Server::CommandResolve(string cmd) {
    vector<string> comm = EZTools::format(cmd, ' ');


}
