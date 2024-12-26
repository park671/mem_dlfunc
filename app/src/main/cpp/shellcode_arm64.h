//
// Created by Park Yu on 2024/12/26.
//

#ifndef MEM_DLFUNC_SHELLCODE_ARM64_H
#define MEM_DLFUNC_SHELLCODE_ARM64_H

typedef uint32_t Inst;
typedef uint64_t Addr;

#ifdef __cplusplus
extern "C" {
#endif

void *createDirectJumpShellCode(uint8_t regIndex, Addr targetAddress);

#ifdef __cplusplus
};
#endif

#endif //MEM_DLFUNC_SHELLCODE_ARM64_H
