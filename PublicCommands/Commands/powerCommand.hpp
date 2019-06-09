#ifndef PUBLICCLIENT_POWERCOMMAND_HPP
#define PUBLICCLIENT_POWERCOMMAND_HPP

#include "EZOutput.h"

class powerCommand :public file{
public:
    powerCommand(string name) : file(name) {}

    Json::Value run();

};

class power : public EZCommand {
public:
    power();

    void init(EZIO *r);

    ~power();

};


#endif //PUBLICCLIENT_VIEWCOMMAND_HPP
