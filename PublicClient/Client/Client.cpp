#include "Client.hpp"
#include <ClientShell.hpp>
#include <EZInput.hpp>
#include <json/json.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <zconf.h>
#include <sstream>


Client::Client() {
    this->pre = "➜ ";
}

string Client::Jsend() {

    ClientToServer *CTS = new ClientToServer();

    Json::Value value;
    Json::FastWriter fw;

    value["pwd"] = this->pwd;
    value["cmd"] = this->str;
    value["btn"] = this->btn;

    return CTS->talk(fw.write(value));
}

void Client::Jtab(string str) {
    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());

    /**
     * @todo模拟服务端发送的数据做测试用
     * */
//    Json::Value value;
//    Json::FastWriter fw;
//    Json::Value arrayValue;
//    for (int i = 0; i < 10; i++)
//    {
//        Json::Value new_item;
//        stringstream ss;
//        ss<<i;
//        new_item["value"] = "testtestt";
//        arrayValue.append(new_item);  // 插入数组成员
//    }
//
//    value["data"] = arrayValue;
//
//    str = fw.write(value);

    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    //printf("%d\n", size.ws_col);
    int format = 0;
    int line = size.ws_col / 8;
    Json::Value root;
    if (readerinfo->parse(str, root)) {
        if (root["data"].isArray()) {
            for (int i = 0; i < root["data"].size(); i++) {
                int tmp = (int)(root["data"][i]["value"].asString().length() / 8);
                format = tmp > format ? tmp : format;
                //cout << (root["data"][i]["value"].asString().length() / 8);
            }
            for (int i = 0; i < root["data"].size(); i++) {
                for (int x = line / (format + 1); i % x == 0;){

                    cout << endl;
                    break;
                }
                cout << root["data"][i]["value"].asString();
                for (int j = format; j >= 0; j--) {
                    cout << "\t";
                }
            }
            //cout << root["data"].asString() << endl;
        }
    }

    printf("\n");
    printf("%s %s%s",
           Input::setColorByStatus(this->pre, 4).c_str(),
           Input::setColorByStatus(this->pwd, 2).c_str(),
           this->str.c_str());
}

void Client::Jout(string out) {

    Json::Reader *readerinfo = new Json::Reader(Json::Features::strictMode());
    int format = 0;

    Json::Value root;
    if (readerinfo->parse(out, root)) {
        if (root["cmd"].isString()) {
            cout << root["cmd"].asString() << endl;
        }

        if (root["btn"].isString()) {
            this->btn = root["btn"].asString();
        }

        if (root["pwd"].isString()) {
            this->pwd = root["pwd"].asString();
        }

        if (root["data"].isArray()) {
            for (int i = 0; i < root['data'].size(); i++) {
                int tmp = (int)(root["data"][i]["key"].asString().length() / 8);
                format = tmp > format ? tmp : format;
            }
            for (int i = 0; i < root['data'].size(); i++) {
                cout << root["data"][i]["key"];
                for (int j = format; j >= 0; j--) {
                    cout << "\t";
                }
                cout << root["data"][i]["value"] << endl;
            }
            cout << root["data"].asString() << endl;
        }
    }

    ::delete readerinfo;
    readerinfo = NULL;
}

void Client::ShellInput() {

    ClientShell *CS = new ClientShell();

    this->pwd = "/";
    while (true) {
        this->str = "";
        printf("%s %s",
               Input::setColorByStatus(this->pre, CS->getState()).c_str(),
               Input::setColorByStatus(this->pwd, 2).c_str());

        while (true) {
            system(STTY_CLOSE TTY_PATH);

            char c = this->Input();

            if (c == '\n' || c == 13) {
                printf("%c", c);
                this->btn = "cmt";
                system(STTY_OPEN TTY_PATH);
                break;
            }
        }

        if (this->str == "exit") {
            printf("\n");
            break;
        }
        this->mem.push_back(this->str);

        printf("\n");
        this->Jout(this->Jsend());
    }
}