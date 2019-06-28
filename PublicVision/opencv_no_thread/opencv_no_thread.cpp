#include "opencv_no_thread.h"
#include "../yolo/yolo.h"
#include "../camera/camera.h"
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#include <base64.h>

opencv_no_thread::opencv_no_thread() : file("opencv_no_thread") {}

Json::Value opencv_no_thread::run() {
    //EZIO *cap = Camera::GET_CAMERA_NODE()->searchChild("capture");
    yolo *GYOLO = Camera::GET_YOLO();
    this->res = GYOLO->getRes();
    this->res["opencv"] = true;
    return this->res;
}
