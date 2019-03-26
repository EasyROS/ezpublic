#include "CommandsBinding.h"

void CMD::binding(EZIO *p) {
    (new ls())->init(p);
    (new cd())->init(p);
}