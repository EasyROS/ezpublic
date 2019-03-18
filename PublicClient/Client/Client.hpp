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

    char Input() {
        char c = getchar();
        switch (c) {
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
                if (this->str.length() > 0) {
                    this->str = this->str.substr(0, this->str.length() - 1);
                    this->printline();
                }
                break;
            case 91:
                this->Input();
                break;
            case 65:
                this->UP();
                //printf("UP");
                break;
            case 66:
                this->DN();
                //printf("DN");
                break;
            case 68:
                this->LF();
                //printf("LF");
                break;
            case 67:
                this->RT();
                //printf("RT");
                break;
            case 27:
                this->Input();
                break;
            case 13:
                printf("%c", c);
                this->index = 0;
                this->str = this->str + this->fix;
                break;
            default:
                this->str += c;
                this->index++;
                this->printline();
        }
        return c;
    }

    string UP();

    string DN();

    string LF() {
        if (this->index > 0) {
            this->index--;
            this->fix.insert(this->fix.begin(), this->str[index]);
            this->str.erase(this->str.end() - 1);
            printf("\b");
        }
    }

    string RT() {
        if (this->index < this->str.length() + this->fix.length()) {
            this->str.push_back(this->fix[0]);
            this->fix.erase(this->fix.begin());
            printf("%c", this->str[index]);
            this->index++;
        }
    }

    void printline();

    int index;
    int memindex;
    string str;
    string pre;
    string pwd;
    string btn;
    string fix;
    vector<string> mem;
};


#endif //PUBLICCLIENT_CLIENT_HPP
