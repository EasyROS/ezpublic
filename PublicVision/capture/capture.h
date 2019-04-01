#ifndef PUBLICVISION_CAPTURE_H
#define PUBLICVISION_CAPTURE_H

#include <EZOutput.h>
#include <zmq.hpp>

class capture: public file{
public:
    capture();

    Json::Value run();

};

class show: public file{
public:
    show();

    Json::Value run();

};
#endif //PUBLICVISION_CAPTURE_H
