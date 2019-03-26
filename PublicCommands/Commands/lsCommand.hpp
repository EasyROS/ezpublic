#ifndef PUBLICCLIENT_LSCOMMAND_HPP
#define PUBLICCLIENT_LSCOMMAND_HPP

#include "EZOutput.h"

class lsCommand : public file {
public:
    lsCommand(string name) : file(name) {}

    Json::Value run();

};

class ls : public EZCommand {
public:
    ls();

    void init(EZIO *r);

    ~ls();

private:
    string pwd;
};

#endif //PUBLICCLIENT_LSCOMMAND_HPP
