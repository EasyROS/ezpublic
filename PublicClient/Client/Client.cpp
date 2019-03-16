#include "Client.hpp"
#include <ClientShell.hpp>
#include <EZInput.hpp>
Client::Client() {
    this->pre = "➜ ";
}

void Client::ShellInput() {

    ClientToServer *CTS = new ClientToServer();
    ClientShell *CS = new ClientShell();

    CTS->talk("ShellInput");

    while (true) {
        this->str = "";
        printf("%s",Input::setColorByStatus(this->pre, CS->getState()).c_str());
        while (true) {
            system(STTY_CLOSE TTY_PATH);

            char c = this->Input();

            if(c == '\n' || c == 13){
                printf("%c", c);
                system(STTY_OPEN TTY_PATH);
                break;
            }
        }

        if (this->str == "exit"){
            printf("\n");
            break;
        }
        this->mem.push_back(this->str);
        printf("\n");
        CTS->talk(this->str);
        //printf("\n%s\t\t\t%d\n",this->str.c_str(),this->str.length());
        //cout << str << "\t\t\t" << this->str.length() << endl;
    }
}