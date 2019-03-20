#include "lsCommand.hpp"
#include <EZOutput.h>
#include <Server.h>

class ls_command : public file {
public:
    ls_command(string name) : file(name) {}

    void run() {
        cout << "test_run" << endl;
    }
};

class ls : public EZCommand {
public:
    ls() {
        this->Command = new ls_command("ls");
    }
    void init(EZIO * r){
        r->Add(this->Command);
        this->Command->set_global()->set_exec()->set_hidden();
    }

    ~ls() {
        delete this->Command;
        delete this;
    }

};
