//
// Created by Park Yu on 2024/12/26.
//

#include <string.h>
#include <stdlib.h>
#include "shellcode_arm64.h"
#include "executable_mem.h"
#include "stdint.h"
#include "log.h"

void *createDirectJumpShellCode(uint8_t regIndex, Addr targetAddress) {
    if (regIndex & ~0x1F) {
        LOGE("invalid reg: %d", regIndex);
        return NULL;
    }
    Inst instLdr = 0x58000040 | regIndex;
    Inst instBr = 0xD61F0000 | (regIndex << 5);
    size_t shellcode_size = sizeof(Inst) * 4;
    Inst *shellCode = (Inst *) malloc(shellcode_size);//2 instLdr + 1 addr
    shellCode[0] = instLdr;
    shellCode[1] = instBr;
    ((Addr *) shellCode)[1] = targetAddress;
    void *result = createExecutableMemory((unsigned char *) shellCode, shellcode_size);
    free(shellCode);
    return result;
}