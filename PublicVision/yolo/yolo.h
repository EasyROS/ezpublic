#ifndef PUBLICVISION_YOLO_H
#define PUBLICVISION_YOLO_H

#include "darknet.h"
#include <opencv2/opencv.hpp>
#include <json/json.h>
#include <EZOutput.h>

class yolo {
public:
    yolo();
    void init();
    cv::Mat detect(cv::Mat img);
    cv::Mat pullImg();
    Json::Value getRes();
};

class YOLO : public file {
public:
    YOLO();

    Json::Value run();
};

#endif //PUBLICVISION_YOLO_H
