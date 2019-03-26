#include "CommandsBinding.h"
#include "ResolveCMD.h"

int main(){
    EZIO *pRoot = new directory("/");
    CMD::binding(pRoot);

    EZIO *ctest = new directory("ctest");

    pRoot->Add(ctest->set_not_global()->set_display()->set_not_exec());
    ctest->Add((new directory("tecst1"))->set_not_global()->set_display()->set_not_exec());
    ctest->Add((new directory("test2"))->set_not_global()->set_display()->set_not_exec());

    //pRoot->run();

    Json::FastWriter fw;
    cout << pRoot->getChildren()[0]->get_name() << fw.write(RCMD::resolve(pRoot,"ls /","cmt","/"));
    return 0;
}