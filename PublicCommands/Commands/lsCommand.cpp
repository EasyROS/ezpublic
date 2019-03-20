#include "lsCommand.hpp"
#include <Server.h>

Json::Value lsCommand::run() {

    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;
    
    Json::Value res;

    EZIO * R = this->parent;

    if(this->btn == "cmt"){
        for(int i = 0; i < R->getChildren().size(); i++){
            if(!R->getChildren()[i]->_hidden())
                res.append(R->getChildren()[i]->get_name());
        }

    }
    if(this->btn == "tab"){
        ////check cmd
        for(int i = 0; i < R->getChildren().size(); i++){
            res.append(R->getChildren()[i]->get_name());
        }
    }

    value["res"] = res;
    return value;
}

ls::ls() {
    this->Command = new lsCommand("ls");
}

void ls::init(EZIO *r) {
    r->Add(this->Command);
    this->Command->set_global()->set_exec()->set_hidden();
}

ls::~ls() {
    delete this->Command;
    delete this;
}
