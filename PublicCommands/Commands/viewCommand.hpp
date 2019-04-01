#ifndef PUBLICCLIENT_VIEWCOMMAND_HPP
#define PUBLICCLIENT_VIEWCOMMAND_HPP

#include "EZOutput.h"

class viewCommand :public file{
public:
    viewCommand(string name) : file(name) {}

    Json::Value run();

};

class view : public EZCommand {
public:
    view();

    void init(EZIO *r);

    ~view();

};


#endif //PUBLICCLIENT_VIEWCOMMAND_HPP
