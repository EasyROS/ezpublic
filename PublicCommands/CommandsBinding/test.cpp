#include "CommandsBinding.h"


int main(){
    EZIO *pRoot = new directory("/");
    CMD::binding(pRoot);
    //pRoot->run();
    Json::FastWriter fw;
    pRoot->getChildren()[0]->cmd = "tab l/l";
    cout << pRoot->getChildren()[0]->get_name() << fw.write(pRoot->getChildren()[0]->run());
    return 0;
}