#include "lsCommand.hpp"
#include "cdCommand.hpp"
#include <iostream>

using namespace std;

int main() {

    EZIO *pRoot = new directory("/");
    ls *LS = new ls();
    (new cd())->init(pRoot);

    LS->init(pRoot);

    LS->Command->pwd = "/";
    LS->Command->cmd = "ls";
    LS->Command->btn = "cmt";

    LS->Command->run();

    return 0;
}