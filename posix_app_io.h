/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef POSIX_APP_IO_H
#define POSIX_APP_IO_H

typedef struct _memory {
    
    void * ptr;
    size_t length;
    
    const char * location;
    
    int file;
    
} Memory;
#define MEMORY_DEFINED

#endif /* POSIX_APP_IO_H */

