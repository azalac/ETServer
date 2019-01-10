/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef DRIVER_IO_H
#define DRIVER_IO_H

#include "proto.h"

#include <endian.h>
#include <string.h>

#ifdef __linux__
#include "posix_driver_io.h"
#endif
#ifdef __WIN32__
#include "win_driver_io.h"
#endif

#define IO_OK 0
#define IO_FAIL 1


#define driver_send_var(driver, var) driver_send_buffer(driver, var, sizeof(*var))

#define driver_recv_var(driver, var) driver_recv_buffer(driver, var, sizeof(*var), NULL)



#define driver_start_message(driver, message_code) driver_send(driver, message_code)

#define driver_recv_message(driver, message_code) driver_recv(driver, message_code)



int driver_init(DriverInstance * driver);

int driver_deinit(DriverInstance * driver);


int driver_send_buffer(DriverInstance * driver, void * buffer, int n);

int driver_recv_buffer(DriverInstance * driver, void * buffer, int n);


int inline driver_send_string(DriverInstance * driver, char * str) {
    
    int str_length = strlen(str) + 1;
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    char len[] = {(char)str_length, (char)(str_length >> 8)};
#elif __BYTE_ORDER == __BIG_ENDIAN
    char len[] = {(char)(str_length >> 8), (char)str_length};
#endif
    
    return driver_send_buffer(driver, len, 2) || driver_send_buffer(driver, str, str_length);
}

int inline driver_recv_string(DriverInstance * driver, char * str, int n) {
    
    char len[2];
    
    if(!driver_recv_buffer(driver, len, 2)) {
        return IO_FAIL;
    }
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    int str_length = len[0] | (len[1]<<8);
#elif __BYTE_ORDER == __BIG_ENDIAN
    int str_length = len[1] | (len[0]<<8);
#endif
    
    if(str_length < n) {
        n = str_length;
    }
    
    return driver_recv_buffer(driver, str, n);
}

int inline driver_recv_string_alloc(DriverInstance * driver, char ** str, int * n) {
    
    char len[2];
    
    if(!driver_recv_buffer(driver, len, 2)) {
        return IO_FAIL;
    }
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    int str_length = len[0] | (len[1]<<8);
#elif __BYTE_ORDER == __BIG_ENDIAN
    int str_length = len[1] | (len[0]<<8);
#endif
    
    *str = (char*)malloc(str_length);
    *n = str_length;
    
    return driver_recv_buffer(driver, *str, str_length);
}


#endif /* DRIVER_IO_H */

