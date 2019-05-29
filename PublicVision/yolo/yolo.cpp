#include "yolo.h"
#include "../camera/camera.h"
#include <boost/thread.hpp>
#include <base64.h>
#include <fstream>

using namespace std;
using namespace cv;

string yolo_err = "";
network *net;
vector<string> classNamesVec;

yolo::yolo() {
    init();
}

void yolo::init() {
    printf("init--yolo\n");

    string cfgfile = "/home/dean/dean.test/darknet/cfg/yolov2.cfg";//读取模型文件，请自行修改相应路径
    string weightfile = "/home/dean/dean.test/darknet/yolov2.weights";
    net = load_network((char *) cfgfile.c_str(), (char *) weightfile.c_str(), 0);//加载网络模型
    set_batch_network(net, 1);
    ifstream classNamesFile("/home/dean/dean.test/darknet/data/coco.names");//标签文件coco有80类
    if (classNamesFile.is_open()) {
        string className = "";
        while (getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }
}

float get_colors[6][3] = {{1, 0, 1},
                          {0, 0, 1},
                          {0, 1, 1},
                          {0, 1, 0},
                          {1, 1, 0},
                          {1, 0, 0}};

float yolo_get_color(int c, int x, int max) {
    float ratio = ((float) x / max) * 5;
    int i = floor(ratio);
    int j = ceil(ratio);
    ratio -= i;
    float r = (1 - ratio) * get_colors[i][c] + ratio * get_colors[j][c];
    return r;
}

cv::Mat yolo::detect() {
    cv::Mat
    mat = pullImg();
    EZIO *yl = Camera::GET_CAMERA_NODE()->searchChild("yolo");

    float m_table[256];
    for (int i = 0; i < 256; i++)
    {
        m_table[i] = i * 1.0 / 255.0f;
    }
    float thresh = 0.5;//参数设置
    float nms = 0.35;
    int classes = 80;
    image im = make_image(mat.cols, mat.rows, mat.channels());
    for(int c = 0; c < mat.channels(); ++c){
        for(int y = 0; y < mat.rows; ++y){
            for(int x = 0; x < mat.cols; ++x){
                im.data[c*im.h*im.w + y*im.w + x] = m_table[mat.data[y*mat.step + x*mat.channels() + c]];        //m_table替代赋值操作，加速转换过程
            }
        }
    }
    image in_s = resize_image(im, net->w, net->h);
    layer l = net->layers[net->n - 1];
    network_predict(net, in_s.data);//网络推理
    int nboxes = 0;
    detection *dets = get_network_boxes(net, im.w, im.h, thresh, 0.5, 0, 1, &nboxes);

    if (nms) {
        do_nms_sort(dets, nboxes, classes, nms);
    }
    vector<cv::Rect>
    boxes;
    boxes.clear();
    vector<int>
    classNames;

    for (int i = 0; i < nboxes; i++) {
        bool flag = 0;
        int className;
        for (int j = 0; j < classes; j++) {
            if (dets[i].prob[j] > thresh) {
                if (!flag) {
                    flag = 1;
                    className = j;
                }
            }
        }
        if (flag) {
            int left = (dets[i].bbox.x - dets[i].bbox.w / 2.) * mat.cols;
            int right = (dets[i].bbox.x + dets[i].bbox.w / 2.) * mat.cols;
            int top = (dets[i].bbox.y - dets[i].bbox.h / 2.) * mat.rows;
            int bot = (dets[i].bbox.y + dets[i].bbox.h / 2.) * mat.rows;

            if (left < 0)
                left = 0;
            if (right > mat.cols - 1)
                right = mat.cols - 1;
            if (top < 0)
                top = 0;
            if (bot > mat.rows - 1)
                bot = mat.rows - 1;

            cv::Rect box(left, top, fabs(left - right), fabs(top - bot));
            boxes.push_back(box);
            classNames.push_back(className);
        }
    }
    free_detections(dets, nboxes);

    for (int i = 0; i < boxes.size(); i++) {
        int offset = classNames[i] * 123457 % 80;
        float red = 255 * yolo_get_color(2, offset, 80);
        float green = 255 * yolo_get_color(1, offset, 80);
        float blue = 255 * yolo_get_color(0, offset, 80);

        rectangle(mat, boxes[i], cv::Scalar(blue, green, red), 2);

        String label = String(classNamesVec[classNames[i]]);
        int baseLine = 0;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        putText(mat, label, Point(boxes[i].x, boxes[i].y + labelSize.height),
                FONT_HERSHEY_SIMPLEX, 1, Scalar(red, blue, green), 2);
    }
    free_image(im);
    free_image(in_s);
    return mat;
}

Json::Value yolo::getRes() {
    cv::Mat
    img = detect();
    std::vector<unsigned char> data_encode;
    int res = imencode(".jpg", img, data_encode);
    std::string str_encode(data_encode.begin(), data_encode.end());
    const char *c = str_encode.c_str();
    Json::Value cap_res;
    cap_res["mat"] = base64_encode(c, str_encode.size());
    img.release();
    //printf("getRes");
    //std::cout << Camera::GET_CAMERA_NODE()->searchChild("capture")->get_name() << endl;
    return cap_res;
}

cv::Mat yolo::pullImg() {
    EZIO *cap = Camera::GET_CAMERA_NODE()->searchChild("capture");
    cv::Mat
    img;
    string str = cap->res["mat"].asString();
    try {
        //cout << cap->res["mat"].asString() << endl;
        std::string decoded = base64_decode(str);
        std::vector<uchar> data_decode(decoded.begin(), decoded.end());
        if (!data_decode.empty())
            img = cv::imdecode(data_decode, CV_LOAD_IMAGE_COLOR);

        if (!img.empty())
            return img;
        else
            return pullImg();

    } catch (cv::Exception e) {
        cout << e.err << endl;
    }

    //std::cout << Camera::GET_CAMERA_NODE()->searchChild("capture")->res << endl;

}

YOLOv3::YOLOv3() : file("yolo") {}

void yolo_show_thread() {
    yolo *GYOLO = Camera::GET_YOLO();

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    Json::Value client_res;
    Json::FastWriter fw;
    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());

    cout << "show_thread" << endl;

    try {
        stringstream ss;
        ss << 9901;
        socket.bind(("tcp://*:" + ss.str()).c_str());
        cout << "tcp://*:" + ss.str() << endl;
    } catch (zmq::error_t e) {
        //cout << port << e.what() << endl;
        //port++;
        yolo_err = "port:9901 is already used \n show is running";
    }

    char buffer[1024 * 512] = {0};

    while (true) {
        //cout << YOLO->getRes().asString() << endl;
        Json::Value res = GYOLO->getRes();
        zmq_recv(socket, buffer, sizeof(buffer) - 1, 0);
        string str = buffer;
        if (readerinfo->parse(str, client_res)) {
            if (client_res["view"].asBool()) {
                res["view"] = true;
                strcpy(buffer, fw.write(res).c_str());
            } else {
                res["view"] = false;
                strcpy(buffer, fw.write(res).c_str());
                zmq_send(socket, buffer, strlen(buffer) + 1, 0);
                break;
            }
        }
        //cout << buffer << endl;
        zmq_send(socket, buffer, strlen(buffer) + 1, 0);

        usleep(1);
    }
}

Json::Value YOLOv3::run() {
    Json::Value res;
    boost::thread ct(&yolo_show_thread);
    ct.detach();
    zmq_sleep(1);
    if (yolo_err.empty()) {
        res["view"] = true;
        res["port"] = 9901;
    } else {
        res["err"] = yolo_err;
        res["view"] = false;
    }
    return res;
}
