#include "viewCommand.hpp"
#include <regex.h>
#include <stdio.h>
#include <cstring>
#include <EZTools.hpp>

Json::Value viewCommand::run() {
    Json::Value value;
    value["cmd"] = this->cmd;
    value["pwd"] = this->pwd;
    value["btn"] = this->btn;

    EZIO *T = this->parent;
    vector<string> C = EZTools::format(this->cmd, ' ');
    vector<string> L = EZTools::format(this->pwd + (C.size() > 1 ? C.back() : ""), '/');

    if (this->btn == "cmt") {
        if (C[0] == "view") {
            if (C.size() > 1) {
                for (int j = 0; j < L.size(); j++) {
                    try {
                        T = T->searchChild(L[j]);
                        if (!T->_view() && j == L.size() - 1) {
                            value["err"] = L[j] + " Is Not VIEW";
                            return value;
                        }

                    } catch (char const *e) {
                        if (string(e) == "404")
                            value["err"] = "Directory Not Found :" + L[j];
                        return value;
                    }
                }
                value = T->run();
            }
            if (C.size() == 1) {
                try {
                    value = this->parent->searchChild("Vision")
                            ->searchChild("Camera")
                            ->searchChild("show")->run();
                } catch (char const *e) {
                    if (string(e) == "404")
                        value["err"] = "404 Not Found";
                    return value;
                }
            }
        }
    }
    return value;
}

view::view() {
    this->Command = new viewCommand("view");
}

void view::init(EZIO *r) {
    r->Add(this->Command);
    this->Command->set_global()->set_exec()->set_hidden();
}

view::~view() {
    delete this->Command;
    delete this;
}
