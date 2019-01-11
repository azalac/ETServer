/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   types.h
 * Author: memca
 *
 * Created on January 10, 2019, 5:03 PM
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef __linux__

#include <sys/types.h>
typedef u_int16_t ushort;

#elif defined __WIN32__

#include <stdint.h>
typedef uint16_t ushort;

#endif

#endif /* TYPES_H */

