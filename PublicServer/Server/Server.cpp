#include "Server.h"
#include <CommandsBinding.h>
#include <Vision.h>
#include <ResolveCMD.h>

Server *S = new Server();
void *call(char *str) {
    //cout << str << endl;

    S->StringToJson(str);
    Json::Value res = RCMD::resolve(S->pRoot,
                  S->content["cmd"].asString(),
                  S->content["btn"].asString(),
                  S->content["pwd"].asString()
    );

    EZServer::sendToClient(S->JsonToString(res));
    //cout << S->JsonToString(res) << endl;
}

Server::Server() {
    this->pRoot = new directory("root");
    CMD::binding(this->pRoot);
    Vision::init(this->pRoot);
}

string Server::JsonToString(Json::Value value) {
    Json::FastWriter fw;

    return fw.write(value);
}

void Server::StringToJson(string str) {
    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());
    if(readerinfo->parse(str, this->content)){
        //cout << "reader succ" << endl;
    }
}

Server* ServerSTD::getS() {
    return S;
}

void Server::Start() {
    out::listen(call);
}