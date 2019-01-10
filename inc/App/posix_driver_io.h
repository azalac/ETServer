/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef POSIX_DRIVER_IO_H
#define POSIX_DRIVER_IO_H

typedef struct _driverinstance {
    int fd;
    const char * file;
} DriverInstance;

#endif /* POSIX_DRIVER_IO_H */

