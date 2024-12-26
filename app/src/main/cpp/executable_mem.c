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
    LOGD("mem=%p\n", mem);
    memset(mem, 0, size);
    memcpy(mem, binary, size);
    LOGD("---binary---\n");
    for (int i = 0; i < size; i++) {
        LOGD("%02X\n", binary[i]);
    }
    LOGD("---binary---\n");
    return mem;
}

int releaseExecutableMemory(void *memory, size_t size) {
    return munmap(memory, size);
}