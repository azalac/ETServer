/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef APP_IO_H
#define APP_IO_H

#define INIT_FAIL -1
#define INIT_OK 0

#ifdef __linux__
#include "posix_app_io.h"
#endif

#ifdef WIN32
#include "win_app_io.h"
#endif

#ifndef MEMORY_DEFINED
#error("[app_io.h]: Memory is not defined, building on unknown platform")
#endif

int initialize_memory(Memory * memory, size_t size, const char * location);

int resize(Memory * memory, size_t new_size);

int deinitialize(Memory * memory);

#endif /* APP_IO_H */

