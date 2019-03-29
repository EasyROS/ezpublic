#include "ResolveCMD.h"

#include <regex.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <EZTools.hpp>

using namespace std;

Json::Value RCMD::resolve(EZIO *pRoot, string cmd, string btn, string pwd) {
    vector<string> C = EZTools::format(cmd, ' ');
    vector<string> L = EZTools::format(pwd + (C.size() > 1 ? C.back() : ""), '/');

    ///cmd cd ../Vi
    ///pwd /Vision/../Vi

    EZIO *T = pRoot;
    Json::Value value;
    value["cmd"] = cmd;
    value["pwd"] = pwd;
    value["btn"] = btn;

    if (cmd == "")
        return value;

    Json::Value res;
    Json::Value obj;

    for (int j = 0; j < L.size() - 1; j++) {
        try {
            T = T->searchChild(L[j]);
            //cout << T->get_name() << endl;
        } catch (char const *e) {
            if (string(e) == "404")
                value["err"] = string(e) + " Not Found " + L[j];
            return value;
        }
    }

    if (btn == "tab") {
        string pre = cmd.substr(0, cmd.length() - L.back().length());
        string pattern = "^" + L.back() + "\\S*";
        const size_t nmatch = 10;
        regmatch_t pm[10];
        regex_t reg;
        regcomp(&reg, pattern.c_str(), REG_EXTENDED | REG_NOSUB);

        if (C.size() <= 1)
            for (int i = 0; i < pRoot->getChildren().size(); i++) {
                if (pRoot->getChildren()[i]->_hidden() &&
                    pRoot->getChildren()[i]->_global() &&
                    pRoot->getChildren()[i]->_exec() &&
                    !regexec(&reg, pRoot->getChildren()[i]->get_name().c_str(), nmatch, pm, REG_NOTEOL) ==
                    REG_NOMATCH) {
                    obj["value"] = "";
                    obj["key"] = pRoot->getChildren()[i]->get_name();
                    res.append(obj);
                }
            }

        for (int i = 0; i < T->getChildren().size(); i++) {
            //cout << T->getChildren()[i]->get_name() << pattern << endl;
            if (!regexec(&reg, T->getChildren()[i]->get_name().c_str(), nmatch, pm, REG_NOTEOL) == REG_NOMATCH
                && !T->getChildren()[i]->_hidden()
                && !T->getChildren()[i]->_global()) {
                obj["value"] = "";
                obj["key"] = T->getChildren()[i]->get_name();
                res.append(obj);
            }
        }
        if(res.size() == 1)
            value["cmd"] = pre + res[0]["key"].asString();
    }
    if (btn == "cmt") {
        int i = 0;
        for (; i < pRoot->getChildren().size(); i++) {
            if (C[0] == pRoot->getChildren()[i]->get_name() &&
                pRoot->getChildren()[i]->_hidden() &&
                pRoot->getChildren()[i]->_global() &&
                pRoot->getChildren()[i]->_exec()) {

                pRoot->getChildren()[i]->cmd = cmd;
                pRoot->getChildren()[i]->pwd = pwd;
                pRoot->getChildren()[i]->btn = btn;

                return pRoot->getChildren()[i]->run();
            }
        }
        if (i == pRoot->getChildren().size()) {
            value["err"] = "Command Not Found";
        }
    }
    value["data"] = res;
    return value;
}