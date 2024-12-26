#include <jni.h>
#include <dlfcn.h>
#include "fake_dlfcn.h"
#include "log.h"
#include "art_13_0.h"
#include "executable_mem.h"
#include "shellcode_arm64.h"

typedef unsigned char byte;

/**
 * art::Thread::RunEmptyCheckpoint()
 * is a .dynsym func, exported
 */
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_park_dlfunc_NativeBridge_testDynSymFunc(JNIEnv *env, jclass clazz) {
    LOGD("test .dynsym func");
    void *artHandle = dlopen_ex("libart.so", RTLD_NOW);
    void *func = dlsym_ex(artHandle, "_ZN3art6Thread18RunEmptyCheckpointEv");
    LOGD("art::Thread::RunEmptyCheckpoint() address=%p", func);
    dlclose_ex(artHandle);
    return func != 0;
}

/**
 * art::DexFile_openInMemoryDexFilesNative()
 * is a .symtab func, not exported
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

static void *GetArtMethod(JNIEnv *env, jobject method) {
    jclass methodClass = env->GetObjectClass(method);
    jfieldID artMethodFieldID = env->GetFieldID(methodClass, "artMethod", "J");
    if (artMethodFieldID == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<void *>(env->GetLongField(method, artMethodFieldID));
}

static constexpr uint32_t kAccPublic = 0x0001;  // class, field, method, ic
static constexpr uint32_t kAccPrivate = 0x0002;  // field, method, ic
static constexpr uint32_t kAccProtected = 0x0004;  // field, method, ic

bool verifyMethodSize(JNIEnv *env, jobject method1, jobject method2) {
    void *artMethod1 =
            GetArtMethod(env, method1);
    void *artMethod2 =
            GetArtMethod(env, method2);
    LOGD("ArtMethod1 addr=%p\n", artMethod1);
    LOGD("ArtMethod2 addr=%p\n", artMethod2);
    size_t artMethodCompileSize = sizeof(art::mirror::ArtMethod);
    size_t artMethodRuntimeSize = ((uint64_t) artMethod2 - (uint64_t) artMethod1);
    LOGD("ArtMethod compile size=%zu\n", artMethodCompileSize);
    LOGD("ArtMethod runtime size=%zu\n", artMethodRuntimeSize);

    unsigned char *copiedArtMethod = (unsigned char *) malloc(artMethodRuntimeSize);
    memcpy(copiedArtMethod, artMethod1, artMethodRuntimeSize);
    for (int i = 0; i < artMethodRuntimeSize; i++) {
        LOGD("%02X", copiedArtMethod[i]);
    }
    art::mirror::ArtMethod *artMethod = static_cast<art::mirror::ArtMethod *>(artMethod1);
    LOGD("ptr_sized_fields_.data_=%p", artMethod->ptr_sized_fields_.data_);
    LOGD("ptr_sized_fields_.quick=%p",
         artMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_);
    return artMethodCompileSize == artMethodRuntimeSize;
}

static void *backup_method_ptr;
static void *hook_stub_method_ptr;

static void (*shell_code_func)();

static art::mirror::ArtMethod *inHookArtMethod;

extern "C" Addr getBackupMethodPtr() {
    return ((Addr) shell_code_func);
}

extern "C" void parkHookBefore() {
    LOGD("parkHookBefore()");
}

extern "C" void parkHookAfter() {
    LOGD("parkHookAfter()");
}

extern "C" void
hookStub(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7);

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_park_dlfunc_NativeBridge_injectTrampoline(JNIEnv *env, jclass clazz, jobject method) {
    void *artMethod1 = GetArtMethod(env, method);
    inHookArtMethod = static_cast<art::mirror::ArtMethod *>(artMethod1);
    backup_method_ptr = inHookArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_;
    LOGD("origin quick=%p", backup_method_ptr);
    Addr origin_addr_val = (Addr) backup_method_ptr;
    shell_code_func = (void (*)()) createDirectJumpShellCode(9, origin_addr_val);
    hook_stub_method_ptr = (void *) hookStub;
    LOGD("hook addr=%p, shell code=%p", hook_stub_method_ptr, shell_code_func);
    inHookArtMethod->ptr_sized_fields_.entry_point_from_quick_compiled_code_ = hook_stub_method_ptr;
    return JNI_TRUE;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_park_dlfunc_NativeBridge_initEnv(JNIEnv *env, jclass clazz, jobject m1, jobject m2) {
    if (verifyMethodSize(env, m1, m2)) {
        return JNI_TRUE;
    } else {
        return JNI_FALSE;
    }
}