/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef DATA_H
#define DATA_H

#include "vector.h"

#define INIT_OUT_OF_SPACE -2
#define INIT_XML_ERROR -1

typedef struct _bone {
    int id;

    Vec3 euler_rotation;
} TrackerBone;

typedef struct _rotlimit {
    double min, max;
    int allowed : 1;
    int around_outer : 1;
    int bounded : 1;
} RotLimit;

typedef struct _boneproto {
    int id;

    const char * name;

    RotLimit rotation[3];

    double length;

    struct _boneproto *children, *next, *parent;
    
} BonePrototype;

int init_bone_structure(const char * definition_file, BonePrototype ** proto);

int fill_bone_buffer(BonePrototype * root, void * buffer, int buffer_size);



#endif /* DATA_H */
