#include "Server.h"
#include <CommandsBinding.h>
#include <ResolveCMD.h>

Server *S = new Server();
void *call(char *str) {
    cout << str << endl;

    S->StringToJson(str);
    Json::Value res = RCMD::resolve(S->pRoot,
                  S->content["cmd"].asString(),
                  S->content["btn"].asString(),
                  S->content["pwd"].asString()
    );

    EZServer::sendToClient(S->JsonToString(res));
    cout << S->JsonToString(res) << endl;
}

Server::Server() {
    this->pRoot = new directory("root");
    this->pRoot->Add(new directory("test"));
    this->pRoot->Add(new directory("test1"));
    this->pRoot->Add(new directory("test2"));
    CMD::binding(this->pRoot);
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

void Server::Start() {
    out::listen(call);
}