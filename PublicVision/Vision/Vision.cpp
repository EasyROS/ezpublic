#include "Vision.h"
#include "../camera/camera.h"

EZIO *V;

EZIO *Vision::GET_VISION_NODE() {
    return V;
}

void Vision::init(EZIO *r) {
    //// this node init
    V = new directory("Vision");
    r->Add(V);
    V->set_dir()->set_display()->set_not_exec();

    //// child node init
    Camera::init(V);
}