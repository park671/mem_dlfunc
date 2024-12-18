//
// Created by Park Yu on 2024/6/18.
//

#ifndef PLUSFRIEND_LOG_H
#define PLUSFRIEND_LOG_H

#include <android/log.h>

#define LOGD(...)  ((void)__android_log_print(ANDROID_LOG_DEBUG, "mem_dlfunc", __VA_ARGS__))
#define LOGI(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "mem_dlfunc", __VA_ARGS__))
#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "mem_dlfunc", __VA_ARGS__))
#define LOGW(...)  ((void)__android_log_print(ANDROID_LOG_WARN, "mem_dlfunc", __VA_ARGS__))
#define LOGE(...)  ((void)__android_log_print(ANDROID_LOG_ERROR, "mem_dlfunc", __VA_ARGS__))

#endif //PLUSFRIEND_LOG_H
