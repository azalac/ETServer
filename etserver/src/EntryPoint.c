
/*
 * File:    EntryPoint.c
 * 
 * Project: Expression PROJECT is undefined on line 8, column 15 in Templates/cFiles/main.c.
 * 
 * Author:  austin-z
 * 
 * First Version: December 12, 2018
 * 
 * Description:
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "App/app_io.h"
#include "data.h"

#include <sys/types.h>

/*
 * 
 */
int main(int argc, char** argv) {

    BonePrototype * proto;
    int size = init_bone_structure("./skeleton_example.xml", &proto);
    
    printf("Buffer size: %d\n", size);
    
    Memory buffer;
    
    if(initialize_memory(&buffer, size, "./bone_buffer.dat")) {
        perror("error initializing IPC memory");
    }
    
    if(fill_bone_buffer(proto, buffer.ptr, size) == INIT_OUT_OF_SPACE) {
        printf("Cannot initialize data buffer: not enough space\n");
    }
    
    if(deinitialize(&buffer) == INIT_FAIL) {
        perror("error deinitializing memory");
    }
    
    return (EXIT_SUCCESS);
}

