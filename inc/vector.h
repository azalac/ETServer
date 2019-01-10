/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef VECTOR_H
#define VECTOR_H

#define VEC_ADD(a, b) (Vec3){a.x + b.x, a.y + b.y, a.z + b.z}

typedef struct _vec3 {
    
    double x, y, z;
    
} Vec3;

#endif /* VECTOR_H */

