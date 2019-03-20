#ifndef PUBLICCOMMANDS_COMMANDSBINDING_H
#define PUBLICCOMMANDS_COMMANDSBINDING_H


/**
 * @todo link header only once in this program
 * @todo add commands headers in this file for bind them
 * @author ls.dean.ch@gmail.com
 * */
#include "../Commands/lsCommand.hpp"
#include "../Commands/cdCommand.hpp"
#include "../Commands/viewCommand.hpp"

namespace CMD{
    ls *LS = new ls();
    cd *CD = new cd();

    void binding(EZIO *p){
        LS->init(p);
        CD->init(p);
    }
}

#endif //PUBLICCOMMANDS_COMMANDSBINDING_H
