#include "struct_optimizer.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compareMembers(const void *a, const void *b) {
    const MemberInfo *memberA = (const MemberInfo *)a;
    const MemberInfo *memberB = (const MemberInfo *)b;

    size_t sizeA = getTypeSize(memberA->type);
    size_t sizeB = getTypeSize(memberB->type);

    if (sizeA < sizeB) return 1;  
    if (sizeA > sizeB) return -1;
    return 0;
}

size_t getTypeSize(const char *type) {
    if (strcmp(type, "char") == 0) return sizeof(char);
    if (strcmp(type, "short") == 0) return sizeof(short);
    if (strcmp(type, "int") == 0) return sizeof(int);
    if (strcmp(type, "float") == 0) return sizeof(float);
    if (strcmp(type, "long") == 0) return sizeof(long);
    if (strcmp(type, "double") == 0) return sizeof(double);
    return 1;  
}

void recalculateOffsets(MemberInfo *members, size_t count) {
    size_t currentOffset = 0;

    for (size_t i = 0; i < count; i++) {
        size_t alignment = getTypeSize(members[i].type);
        if (currentOffset % alignment != 0) {
            currentOffset += alignment - (currentOffset % alignment);
        }

        members[i].offset = currentOffset;
        currentOffset += alignment;
    }
}

size_t calculateStructSize(MemberInfo *members, size_t count) {
    size_t currentOffset = 0;
    size_t largestMemberSize = 0;

    for (size_t i = 0; i < count; i++) {
        size_t alignment = getTypeSize(members[i].type);
        largestMemberSize = (alignment > largestMemberSize) ? alignment : largestMemberSize;

        if (currentOffset % alignment != 0) {
            currentOffset += alignment - (currentOffset % alignment);
        }

        currentOffset += alignment;
    }

    if (currentOffset % largestMemberSize != 0) {
        currentOffset += largestMemberSize - (currentOffset % largestMemberSize);
    }

    return currentOffset;
}

size_t optimizeStruct(MemberInfo *members, size_t count, MemberInfo *result) {
    qsort(members, count, sizeof(MemberInfo), compareMembers);
    memcpy(result, members, count * sizeof(MemberInfo));
    recalculateOffsets(result, count);
    return calculateStructSize(result, count);
}

void printOptimizedStruct(MemberInfo *members, size_t count) {
    MemberInfo *optimizedMembers = malloc(count * sizeof(MemberInfo));

    size_t optimizedSize = optimizeStruct(members, count, optimizedMembers);

    printf("Optimized struct size: %zu bytes\n", optimizedSize);
    printf("Optimized layout:\n");
    for (size_t i = 0; i < count; i++) {
        printf("Name: %s, Type: %s, Offset: %zu\n",
               optimizedMembers[i].name, optimizedMembers[i].type, optimizedMembers[i].offset);
    }

    free(optimizedMembers);
}
