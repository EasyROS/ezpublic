#include "yolo.h"
#include "../camera/camera.h"

yolo::yolo() {
    init();
}

void yolo::init() {
    printf("init");
}

cv::Mat yolo::detect(cv::Mat img) {
    printf("detect");
    return img;
}

Json::Value yolo::getRes() {
    printf("getRes");
    return Camera::GET_CAMERA_NODE()->searchChild("capture")->res;
}

cv::Mat yolo::pullImg() {
    printf("pullImg");
    cv::Mat img;
    std::cout << Camera::GET_CAMERA_NODE()->searchChild("capture")->get_name() << endl;
    return img;
}


YOLO::YOLO() : file("yolo") {}

Json::Value YOLO::run() {
    yolo yl;
    return yl.getRes();
}