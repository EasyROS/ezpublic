#include "lsCommand.hpp"
#include <regex.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <EZTools.hpp>

Json::Value lsCommand::run() {

    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;

    Json::Value res;
    Json::Value obj;

    EZIO *T = this->parent;
    vector<string> C = EZTools::format(this->cmd, ' ');
    vector<string> L = EZTools::format(this->pwd + (C.size() > 1 ? C.back() : ""), '/');
    //cout << C.size() << "\t" << this->cmd + "\t" << C.back() + "\t" << this->pwd + (C.size() > 1 ? C.back() : "") << "\t" << L.size() <<endl;
    string pattern = "^" + L.back() + "\\S*";
    const size_t nmatch = 10;
    regmatch_t pm[10];
    regex_t reg;
    regcomp(&reg, pattern.c_str(), REG_EXTENDED | REG_NOSUB);

    int j = 0;
    for (; j < L.size() - 1; j++) {
        try {
            //cout << L[j] << endl;
            T = T->searchChild(L[j]);
        } catch (char const *e) {
            if (string(e) == "404")
                value["err"] = string(e) + " Not Found " + L[j];
            return value;
        }
    }

    //cout << L.size() << L.back() << T->get_name() << endl;
    if (this->btn == "cmt") {
        if (C[0] == "ls") {
            if (C.size() >= 1) {
                //cout << L.back() << C.back() << endl;
                for (int i = 0; i < T->getChildren().size(); i++) {
                    if (!regexec(&reg, T->getChildren()[i]->get_name().c_str(), nmatch, pm, REG_NOTEOL) == REG_NOMATCH
                        && !T->getChildren()[i]->_hidden()
                        && !T->getChildren()[i]->_global()) {


                        obj["value"] = "";
                        if (T->getChildren()[i]->_file())
                            obj["value"] = T->getChildren()[i]->get_name();
                        obj["key"] = T->getChildren()[i]->get_name();
                        res.append(obj);
                    }
                }
            }
        }
    }

    value["data"] = res;
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
