#include <jni.h>
#include <dlfcn.h>
#include "fake_dlfcn.h"
#include "log.h"

/**
 * _ZN3art6Thread18RunEmptyCheckpointEv is a .dynsym func
 */
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_park_dlfunc_NativeBridge_testDynSymFunc(JNIEnv *env, jclass clazz) {
    LOGD("test .dynsym func");
    void *artHandle = dlopen_ex("libart.so", RTLD_NOW);
    void *func = dlsym_ex(artHandle, "_ZN3art6Thread18RunEmptyCheckpointEv");
    LOGD("art::Thread::RunEmptyCheckpointEv() address=%p", func);
    dlclose_ex(artHandle);
    return func != 0;
}

/**
 * _ZN3artL34DexFile_openInMemoryDexFilesNativeEP7_JNIEnvP7_jclassP13_jobjectArrayS5_P10_jintArrayS7_P8_jobjectS5
 * is a .symtab func
 */
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_park_dlfunc_NativeBridge_testNonDynSymFunc(JNIEnv *env, jclass clazz) {
    LOGD("test .symtab func");
    void *artHandle = dlopen_ex("libart.so", RTLD_NOW);
    void *func = dlsym_ex(artHandle,
                          "_ZN3artL34DexFile_openInMemoryDexFilesNativeEP7_JNIEnvP7_jclassP13_jobjectArrayS5_P10_jintArrayS7_P8_jobjectS5");
    LOGD("art::DexFile_openInMemoryDexFilesNative() address=%p", func);
    dlclose_ex(artHandle);
    return func != 0;
}