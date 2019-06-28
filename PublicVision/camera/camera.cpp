#include "camera.h"
#include "../capture/capture.h"
#include "../yolo/yolo.h"
#include "../opencv_no_thread/opencv_no_thread.h"
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>

EZIO *C;
yolo *Y;
Json::Value res;
EZIO *cap;
bool caprun;

EZIO *Camera::GET_CAMERA_NODE() {
    return C;
}

yolo* Camera::GET_YOLO() {
    return Y;
}

void Camera::init(EZIO *r) {
    C = new directory("Camera");

    r->Add(C);
    C->set_dir()->set_display()->set_not_exec();

    cap = ((new capture())
            ->set_file()
            ->set_exec()
            ->set_display()
            ->set_not_view());
    C->Add((new show())
                   ->set_file()
                   ->set_exec()
                   ->set_display()
                   ->set_view());
    C->Add((new opencv_no_thread())
                   ->set_file()
                   ->set_exec()
                   ->set_display()
                   ->set_view());
    C->Add((new YOLOv3())
                   ->set_file()
                   ->set_exec()
                   ->set_display()
                   ->set_view());
    Y->init();
    C->Add(cap);
    Camera::_Thread_ON();
}

void cap_thread() {
    while (true) {
        res = cap->run();
        if (res["mat"].isString()) {
            caprun = true;
        } else {
            caprun = false;
            cout << "ERROR CAP_THREAD BREAK !!!" << endl;
            break;
        }
    }
}

void Camera::_Thread_ON() {

    boost::thread ct(&cap_thread);
    ct.detach();
}

Json::Value Camera::get() {
    if (caprun)
        return res;
    else {
        res["err"] = "capture is break";
        return res;
    }

}
