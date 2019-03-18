#ifndef EZPUBLIC_SERVER_HPP
#define EZPUBLIC_SERVER_HPP
#include <iostream>
#include <EZOutput.h>
#include <EZTools.hpp>
using namespace std;

class Server {
public:
    Server();

    void CommandResolve(string cmd);

private:
    EZCommand *CMD;

};


#endif EZPUBLIC_SERVER_HPP
