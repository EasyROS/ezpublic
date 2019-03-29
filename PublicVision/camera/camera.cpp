#include "camera.h"

EZIO *C;

EZIO *Camera::GET_CAMERA_NODE() {
    return C;
}

void Camera::init(EZIO *r) {
    C = new directory("Camera");

    r->Add(C);
    C->set_dir()->set_display()->set_not_exec();
}