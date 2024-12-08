#include "struct_optimizer.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t memberCount = 5;

    MemberInfo members[5] = {
        {"a", "char", 0},
        {"c", "double", 0},
        {"d", "short", 0},
        {"f", "long", 0},
        {"g", "long", 0},
    };

    printOptimizedStruct(members, memberCount);

    return 0;
}
