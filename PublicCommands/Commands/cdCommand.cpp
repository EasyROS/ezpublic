#include "cdCommand.hpp"
#include <regex.h>
#include <stdio.h>
#include <cstring>
#include <EZTools.hpp>

Json::Value cdCommand::run() {
    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;

    EZIO *T = this->parent;
    vector<string> C = EZTools::format(this->cmd, ' ');
    vector<string> L = EZTools::format(this->pwd + (C.size() > 1 ? C.back() : ""), '/');


    cout << L.size() << L.back().length() << endl;

    if (this->btn == "cmt") {
        if (C[0] == "cd") {
            if (C.size() > 1) {
                for (int j = 0; j < L.size(); j++) {
                    try {
                        T = T->searchChild(L[j]);
                        if (!T->_dir()) {
                            value["err"] = L[j] + "Is Not Directory";
                            return value;
                        }

                    } catch (char const *e) {
                        if (string(e) == "404")
                            value["err"] = "Directory Not Found :" + L[j];
                        return value;
                    }
                }
                value["pwd"] = EZTools::connect_string(T->getPWD(), '/');
            }
            if (C.size() == 1) {
                value["pwd"] = "/";
            }
        }
    }
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
