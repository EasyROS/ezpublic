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

    bool esc;

    void Jout(string out);

    void Jtab(string str);

    char Input() {
        char c = getchar();
        if (c >= 'A' && c <= 'Z' && this->esc) {
            this->str += c;
            this->index++;
            this->printline();
        } else
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
                    this->esc = false;
                    this->Input();
                    break;
                case 65:
                    this->UP();
                    this->esc = true;
                    break;
                case 66:
                    this->esc = true;
                    this->DN();
                    break;
                case 68:
                    this->LF();
                    this->esc = true;
                    break;
                case 67:
                    this->RT();
                    this->esc = true;
                    break;
                case 27:
                    this->esc = false;
                    this->Input();
                    break;
                case 13:
                    this->esc = true;
                    printf("%c", c);
                    this->index = 0;
                    this->str = this->str + this->fix;
                    break;
                default:
                    this->esc = true;
                    this->str += c;
                    this->index++;
                    this->printline();
            }
        return c;
    }

    void UP();

    void DN();

    void LF() {
        if (this->index > 0) {
            this->index--;
            this->fix.insert(this->fix.begin(), this->str[index]);
            this->str.erase(this->str.end() - 1);
            printf("\b");
        }
    }

    void RT() {
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
