//
// Created by Park Yu on 2024/12/27.
//

#ifndef MEM_DLFUNC_PHOOK_H
#define MEM_DLFUNC_PHOOK_H

#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

bool hookMethod(const char *libName, const char *methodName, void *hookDelegate);

bool unhookMethod();

#ifdef __cplusplus
};
#endif

#endif //MEM_DLFUNC_PHOOK_H
