#include "capture.h"
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>

capture::capture() : file("capture") {}

using namespace cv;

Mat img;
VideoCapture VC(0);
std::vector<unsigned char> data_encode;
Json::Value cap_res;
int port = 9900;

Json::Value capture::run() {
    VC >> img;

    imencode(".png", img, data_encode);
    std::string str_encode(data_encode.begin(), data_encode.end());

    cap_res["mat"] = str_encode;
    return cap_res;
}

show::show() : file("show") {}

void show_thread() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    Json::Value client_res;

    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());

    cout << "show_thread" << endl;

    char buffer[1024] = {0};
    while (true)
        try {
            stringstream ss;
            ss << port;
            socket.bind(("tcp://*:" + ss.str()).c_str());
            break;
        } catch (zmq::error_t e) {
            //cout << port << e.what() << endl;
            port++;
        }

    while (true) {
        cout << "show_thread" << endl;
        zmq_recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (readerinfo->parse(string(buffer), client_res)) {
            if (client_res["view"].asBool()) {
                if (cap_res["mat"].isString())
                    strcpy(buffer, cap_res["mat"].asString().c_str());
                zmq_send(socket, buffer, strlen(buffer) + 1, 0);
            } else {
                break;
            }
        }
        usleep(1);
    }
}


Json::Value show::run() {
    Json::Value res;

    boost::thread ct(&show_thread);
    ct.detach();

    res["view"] = true;
    res["port"] = port;
    return res;
}

