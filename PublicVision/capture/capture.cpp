#include "capture.h"
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#include <base64.h>

capture::capture() : file("capture") {}

using namespace cv;

Mat img;
VideoCapture VC(0);
std::vector<unsigned char> data_encode;
Json::Value cap_res;
int port = 9900;
string err = "";

Json::Value capture::run() {
    VC >> img;

    std::vector<unsigned char> data_encode;
    int res = imencode(".jpg", img, data_encode);
    std::string str_encode(data_encode.begin(), data_encode.end());
    const char *c = str_encode.c_str();

    cap_res["mat"] = base64_encode(c, str_encode.size());
    //cout << cap_res["mat"].asString().size()  << endl;
    return cap_res;
}

show::show() : file("show") {}

void show_thread() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    Json::Value client_res;
    Json::FastWriter fw;
    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());

    cout << "show_thread" << endl;

    try {
        stringstream ss;
        ss << port;
        socket.bind(("tcp://*:" + ss.str()).c_str());
        cout << "tcp://*:" + ss.str() << endl;
    } catch (zmq::error_t e) {
        //cout << port << e.what() << endl;
        //port++;
        err = "port:9900 is already used \n show is running";
    }

    char buffer[1024 * 512] = {0};

    while (true) {
        //cout << port << endl;
        zmq_recv(socket, buffer, sizeof(buffer) - 1, 0);
        string str = buffer;
        if (readerinfo->parse(str, client_res)) {
            if (client_res["view"].asBool()) {
                cap_res["view"] = true;
                strcpy(buffer, fw.write(cap_res).c_str());
            } else {
                cap_res["view"] = false;
                strcpy(buffer, fw.write(cap_res).c_str());
                zmq_send(socket, buffer, strlen(buffer) + 1, 0);
                break;
            }
        }
        zmq_send(socket, buffer, strlen(buffer) + 1, 0);

        usleep(1);
    }
}


Json::Value show::run() {
    Json::Value res;
    boost::thread ct(&show_thread);
    ct.detach();
    zmq_sleep(1);
    if (err.empty()) {
        res["view"] = true;
        res["port"] = port;
    } else {
        res["err"] = err;
        res["view"] = false;
    }
    return res;
}

