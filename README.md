# Project: Optimized Struct Handler
## Introduction
This project provides a set of tools and utilities for optimizing the memory layout of C structs. The main focus of the project is to analyze and reorder struct members to minimize memory usage while adhering to alignment rules.

Key features include:


* Optimizing the struct layout to reduce memory size.
* Printing the optimized layout and its offsets.

## How to Butild and Run
### Static Library
```bash
gcc -c struct_optimizer.c
ar -r libstruct_optimizer.a struct_optimizer.o
gcc -static test.c -L. -lstruct_optimizer -o prog_static
./prog_static
```

### Shared Library with load time linking
```bash
gcc -Og -fpic -c struct_optimizer.c
gcc -shared -o libstruct_optimizer.so struct_optimizer.o
gcc test.c -L. -lstruct_optimizer -o prog_shared
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./prog_shared
```

### Shared Library with run time linking
```bash
gcc -rdynamic -o prog_runtime test_runtime.c -ldl
./prog_runtime
```

## Expected Output
```
Optimized struct size: 32 bytes
Optimized layout:
Name: c, Type: double, Offset: 0
Name: f, Type: long, Offset: 8
Name: g, Type: long, Offset: 16
Name: d, Type: short, Offset: 24
Name: a, Type: char, Offset: 26
```