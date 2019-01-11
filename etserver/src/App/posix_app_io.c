#ifdef __linux__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "app_io.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void check_file_size(int fd, int target_length) {
    struct stat st;
    fstat(fd, &st);
    
    char null[1];
    
    null[0] = 0;
    
    for(int i = st.st_size; i < target_length; i++) {
        write(fd, null, sizeof(null));
    }
}

int initialize_memory(Memory * memory, size_t length, const char * location) {
    
    if(length < 1) {
        errno = EINVAL;
        return INIT_FAIL;
    }
    
    memory->file = open(location, O_RDWR | O_CREAT, 0666);
    
    if(memory->file == -1) {
        perror("Error creating file");
        return INIT_FAIL;
    }
    
    check_file_size(memory->file, length);
    
    memory->ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, memory->file, 0);
    
    if(memory->ptr == MAP_FAILED) {
        close(memory->file);
        perror("Error mapping memory");
        return INIT_FAIL;
    }
    
    memory->length = length;
    memory->location = location;
    
    return INIT_OK;
}

int resize(Memory * memory, size_t new_size) {
    deinitialize(memory);
    
    return initialize_memory(memory, new_size, memory->location);
}

int deinitialize(Memory * memory) {
    if(memory->ptr != 0 && memory->ptr != MAP_FAILED) {
        if(munmap(memory->ptr, memory->length) == -1) {
            return INIT_FAIL;
        }
    }
    
    if(memory->file != -1) {
        if(close(memory->file) == -1) {
            return INIT_FAIL;
        }
    }
}

#endif