#ifndef PUBLICCLIENT_CDCOMMAND_HPP
#define PUBLICCLIENT_CDCOMMAND_HPP

#include "EZOutput.h"


class cdCommand : public file {
public:
    cdCommand(string name) : file(name) {}

    Json::Value run();

};

class cd : public EZCommand {
public:
    cd();

    void init(EZIO *r);

    ~cd();

};


#endif //PUBLICCLIENT_CDCOMMAND_HPP
