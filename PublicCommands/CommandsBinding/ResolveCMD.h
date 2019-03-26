#ifndef PUBLICCOMMANDS_RESOLVECMD_H
#define PUBLICCOMMANDS_RESOLVECMD_H

#include "CommandsBinding.h"

namespace RCMD {
    Json::Value resolve(EZIO *pRoot, string cmd, string btn, string pwd);
}
#endif //PUBLICCOMMANDS_RESOLVECMD_H
