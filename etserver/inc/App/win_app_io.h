/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef WIN_APP_IO_H
#define WIN_APP_IO_H

#include <windows.h>

typedef struct _MemoryImpl {
	HANDLE file, mapping;
} MemoryImpl;

#endif /* WIN_APP_IO_H */
