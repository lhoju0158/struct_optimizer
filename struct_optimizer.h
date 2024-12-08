#ifndef STRUCT_OPTIMIZER_H
#define STRUCT_OPTIMIZER_H

#include <stddef.h>

typedef struct {
    const char *name;  
    const char *type; 
    size_t offset;     
} MemberInfo;

size_t getTypeSize(const char *type);

void recalculateOffsets(MemberInfo *members, size_t count);

size_t calculateStructSize(MemberInfo *members, size_t count);

size_t optimizeStruct(MemberInfo *members, size_t count, MemberInfo *result);

void printOptimizedStruct(MemberInfo *members, size_t count);

#endif 
