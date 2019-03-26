#include "cdCommand.hpp"

Json::Value cdCommand::run() {
    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;

    //EZIO * R = this->parent;

//    if(this->btn == "cmt"){
//        for(int i = 0; i < R->getChildren().size(); i++){
//            cout << R->getChildren()[i]->get_name() << endl;
//        }
//    }
//    if(this->btn == "tab"){
//
//    }
    cout << "cd" << endl;
    return value;
}

cd::cd() {
    this->Command = new cdCommand("cd");
}

void cd::init(EZIO *r) {
    r->Add(this->Command);
    this->Command->set_global()->set_exec()->set_hidden();
}

cd::~cd() {
    delete this->Command;
    delete this;
}
