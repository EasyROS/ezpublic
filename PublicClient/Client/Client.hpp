#ifndef PUBLICCLIENT_CLIENT_HPP
#define PUBLICCLIENT_CLIENT_HPP
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>


#define TTY_PATH "/dev/tty"
#define STTY_CLOSE             "stty raw -echo -F "
#define STTY_OPEN            "stty -raw echo -F "

using namespace std;

class Client {
public:
    Client();

    void ShellInput();

private:
    string Jsend();
    void Jout(string out);
    void Jtab(string str);

    char Input(){
        char c = getchar();
        switch (c){
            case 3:;
                system(STTY_OPEN TTY_PATH);
                printf("\nExit with code 3\n");
                exit(0);
            case 9:
                system(STTY_OPEN TTY_PATH);
                this->btn = "tab";
                this->Jtab(this->Jsend());
                break;
            case 127:
                if(this->str.length() > 0){
                    this->str = this->str.substr(0,this->str.length() - 1);
                    printf("\b \b");
                }
                break;
            case 91:
                this->Input();
                break;
            case 65:
                printf("UP");
                break;
            case 66:
                printf("DN");
                break;
            case 68:
                printf("LF");
                break;
            case 67:
                printf("RT");
                break;
            case 27:
                this->Input();
                break;
            case 13:
                printf("%c", c);
                break;
            default:
                this->str += c;
                printf("%c", c);
        }
        return c;
    }

    string str;
    string pre;
    string pwd;
    string btn;
    vector <string> mem;
    string last;
};


#endif //PUBLICCLIENT_CLIENT_HPP
