/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef APP_IO_H
#define APP_IO_H

#include <stdlib.h>

#define INIT_FAIL -1
#define INIT_OK 0

struct _MemoryImpl;

typedef struct _MemoryImpl MemoryImpl;

#ifdef __linux__
#include "App/posix_app_io.h"
#endif

#ifdef WIN32
#include "App/win_app_io.h"
#endif

typedef struct _memory {
    
    void * ptr;
    size_t len;
    
    const char * location;
    
    MemoryImpl impl;
    
} Memory;

int initialize_memory(Memory * memory, size_t size, const char * location);

int resize(Memory * memory, size_t new_size);

int deinitialize(Memory * memory);

#endif /* APP_IO_H */

