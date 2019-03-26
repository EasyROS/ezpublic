#ifndef EZPUBLIC_SERVER_HPP
#define EZPUBLIC_SERVER_HPP

#include <iostream>
#include <EZOutput.h>
#include <EZTools.hpp>

using namespace std;

class Server {
public:
    Server();

    string JsonToString(Json::Value value);

    void StringToJson(string str);

    void Start();

    EZIO *pRoot;
    Json::Value content;

};

#endif