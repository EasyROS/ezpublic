
#include "Server.h"

#include "boost/thread.hpp"

int main(){
    cout << "Server Startup" << endl;

    /**
     * @todo    Thread cpp in default running
     * @author  ls.dean.ch
     * @param   Thread, Node, argv
     * */

    ///thread function or class
    ///vision thread
    ///tick thread
    ///walk thread
    ///any other thread

    ///default control service @param Server Class
    ServerSTD::getS()->pRoot->Add((new directory("test"))->set_display());
    ServerSTD::getS()->pRoot->Add((new directory("test1"))->set_display());
    ServerSTD::getS()->pRoot->Add((new directory("test2"))->set_display());
    ServerSTD::getS()->Start();
    return 0;
}
