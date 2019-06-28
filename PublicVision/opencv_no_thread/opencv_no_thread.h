#ifndef PUBLICVISION_OPENCV_H
#define PUBLICVISION_OPENCV_H

#include <EZOutput.h>

class opencv_no_thread : public file {
public:
    opencv_no_thread();

    Json::Value run();

};

#endif //PUBLICVISION_CAPTURE_H
