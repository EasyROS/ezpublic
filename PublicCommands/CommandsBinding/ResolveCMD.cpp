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

    EZIO *T = pRoot;
    Json::Value value;
    value["cmd"] = cmd;
    value["pwd"] = pwd;
    value["btn"] = btn;

    Json::Value res;

    for (int j = 0; j < L.size() - 1; j++) {
        try {
            T = T->searchChild(L[j]);
        } catch (char const *e) {
            if (string(e) == "404")
                value["err"] = string(e) + " Not Found " + L[j];
            return value;
        }
    }

    if (btn == "tab") {
        string pattern = "^" + C.back() + "\\S*";
        const size_t nmatch = 10;
        regmatch_t pm[10];
        regex_t reg;
        regcomp(&reg, pattern.c_str(), REG_EXTENDED | REG_NOSUB);

        if (C.size() <= 1)
            for (int i = 0; i < pRoot->getChildren().size(); i++) {
                if (pRoot->getChildren()[i]->_hidden() &&
                    pRoot->getChildren()[i]->_global() &&
                    pRoot->getChildren()[i]->_exec() &&
                    !regexec(&reg, pRoot->getChildren()[i]->get_name().c_str(), nmatch, pm, REG_NOTEOL) == REG_NOMATCH)

                    res.append(pRoot->getChildren()[i]->get_name());
            }

        for (int i = 0; i < T->getChildren().size(); i++) {
            if (!regexec(&reg, T->getChildren()[i]->get_name().c_str(), nmatch, pm, REG_NOTEOL) == REG_NOMATCH
                && !T->getChildren()[i]->_hidden()
                && !T->getChildren()[i]->_global())
                res.append(T->getChildren()[i]->get_name());
        }

        value["res"] = res;
        return value;
    }
    if (btn == "cmt") {
        for (int i = 0; i < pRoot->getChildren().size(); i++) {
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
    }

}