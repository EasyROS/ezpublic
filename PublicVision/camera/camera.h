#ifndef PUBLICVISION_CAMERA_H
#define PUBLICVISION_CAMERA_H

#include <EZOutput.h>
#include "../yolo/yolo.h"
namespace Camera{
    void init(EZIO *r);

    Json::Value get();

    void _Thread_ON();

    EZIO *GET_CAMERA_NODE();

    yolo *GET_YOLO();
}

#endif //PUBLICVISION_CAMERA_H
