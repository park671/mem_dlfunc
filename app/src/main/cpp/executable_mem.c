//
// Created by Park Yu on 2024/1/25.
//

#include "executable_mem.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

void *createExecutableMemory(unsigned char *binary, size_t size) {
    void *mem = mmap(NULL, size, PROT_WRITE | PROT_EXEC,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    LOGD("executable memory addr=%p[%zu byte]\n", mem, size);
    if (size % 4) {
        LOGE("executable memory must alignment to 4Byte (32bit)");
        return NULL;
    }
    memset(mem, 0, size);
    memcpy(mem, binary, size);
    LOGD("---binary---\n");
    for (int i = 0; i < size; i += 4) {
        LOGD("%p:[%02X,%02X,%02X,%02X]\n", (mem + i), binary[i], binary[i + 1], binary[i + 2],
             binary[i + 3]);
    }
    LOGD("---binary---\n");
    return mem;
}

int releaseExecutableMemory(void *memory, size_t size) {
    return munmap(memory, size);
}