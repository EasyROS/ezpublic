
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
    ServerSTD::getS()->pRoot->Add(new directory("test"));
    ServerSTD::getS()->pRoot->Add(new directory("test1"));
    ServerSTD::getS()->pRoot->Add(new directory("test2"));
    ServerSTD::getS()->Start();
    return 0;
}
