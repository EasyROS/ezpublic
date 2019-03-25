#include "lsCommand.hpp"
#include <Server.h>
//#include <boost/regex.hpp>
#include <iostream>

//using namespace boost;

Json::Value lsCommand::run() {

    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;

    Json::Value res;

    EZIO *R = this->parent;
    EZIO *T = this->parent;
    vector<string> C = EZTools::format(this->cmd, ' ');
    vector<string> L = EZTools::format(C.back(), '/');

    cout << C.back() << C.size() << L.size() << endl;

    int j = 0;
    if (C.size() > 1) {
        for (; j < L.size() - 1; j++) {
            try {
                T = T->searchChild(L[j]);
            } catch (char const *e) {
                value["err"] = string(e) + " Not Found " + L[j];
                return value;
            }
        }

    }
    if (this->btn == "cmt") {
        for (int i = 0; i < R->getChildren().size(); i++) {
            if (!R->getChildren()[i]->_hidden())
                res.append(R->getChildren()[i]->get_name());
        }

    }
    if (this->btn == "tab") {
        if (j == L.size() - 1) {
            //regex pattern(L.back() + "*");
            //cmatch what;
            for (int i = 0; i < T->getChildren().size(); i++) {
                //if (regex_search(T->getChildren()[i]->get_name().c_str(), what, pattern))
                    res.append(R->getChildren()[i]->get_name());
            }

        }
        for (int i = 0; i < R->getChildren().size(); i++) {
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
