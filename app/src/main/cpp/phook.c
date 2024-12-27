//
// Created by Park Yu on 2024/12/27.
//


#include "phook.h"
#include "jni.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fake_dlfcn.h"
#include "log.h"
#include "memory_scanner.h"
#include "shellcode_arm64.h"

bool hookMethod(const char *libName, const char *methodName, void *hookDelegate) {
    void *artHandle = dlopen_ex(libName, RTLD_NOW);
    void *func = dlsym_ex(artHandle, methodName);
    LOGD("backup address=%p", func);
    dlclose_ex(artHandle);
    if (func == 0) {
        return JNI_FALSE;
    }
    setTextWritable(libName);
    uint64_t funcAddr = (uint64_t) func;
    if (isFuncWritable(funcAddr)) {
        LOGI("make func writable success");
    } else {
        LOGE("make func writable fail");
    }
    size_t shellCodeByte = 4 * 4;//4inst * 4byte
    Addr backAddr = funcAddr + shellCodeByte;

    void *copiedBackupHeadInst = malloc(shellCodeByte);
    Addr beforeHookAddr = (Addr) hookDelegate;

    void *inlineHookPtr = createInlineHookStub(func, shellCodeByte, beforeHookAddr, backAddr, 9);
    LOGD("inline hook ptr:%p", inlineHookPtr);
    void *jumpCodePtr = createDirectJumpShellCode(9, ((Addr) inlineHookPtr));
    LOGD("shell code ptr:%p", jumpCodePtr);
    memcpy(func, jumpCodePtr, shellCodeByte);
    return func != 0;
}

bool unhookMethod() {
    //todo impl unhook
}