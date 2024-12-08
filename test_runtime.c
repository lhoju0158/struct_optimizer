#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;  
    const char *type;  
    size_t offset;     
} MemberInfo;

typedef void (*printOptimizedStruct_t)(MemberInfo *, size_t);
char *error;


int main() {


    void *handle = dlopen("./libstruct_optimizer.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr,"%s/n",dlerror());
        exit(1);
    }


    printOptimizedStruct_t printOptimizedStruct = (printOptimizedStruct_t)dlsym(handle, "printOptimizedStruct");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr,"%s/n",error);
        dlclose(handle);
        exit(1);
    }

    size_t memberCount = 5;
    MemberInfo members[5] = {
        {"a", "char", 0},
        {"c", "double", 0},
        {"d", "short", 0},
        {"f", "long", 0},
        {"g", "long", 0},
    };

    printOptimizedStruct(members, memberCount);

    if(dlclose(handle)<0){
        fprintf(stderr,"%s/n",dlerror());
        exit(1);
    }

    return 0;
}
