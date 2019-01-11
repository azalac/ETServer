/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef PROTO_H
#define PROTO_H

#include "types.h"

struct Packet {
    ushort message;
    ushort nbytes;
};

enum InfoTypes {
    INT8,
    INT16,
    INT32,
    INT64,
    
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    
    FLOAT,
    DOUBLE,
    
    STRING, // a little-endian short for length, followed by the null-terminated string data
    
    DATA
};

struct AngleInfo {
    int bone_id;
    int8_t axis;
    double angle;
};

struct LengthInfo {
    int bone_id;
    double length;
};

// similar to return statement
// returns data, or confirms that the message was sent if no data needs sending
#define PROTO_RET 0

// checks that the connection to a device is working
#define PROTO_CONNECT 1

// a device information query
#define PROTO_QUERY 2

// queries the value of a specific key (same return format as PROTO_QUERY,
// but only the requested row is returned)
#define PROTO_QUERY_VAL 3

// specifies the key and type for a device information row (type is first byte)
#define PROTO_INFO_KEY 4
// specifies the value for a device information row
#define PROTO_INFO_VAL 5
// ends the device information response
#define PROTO_INFO_END 6

// gets the bone xml description
#define PROTO_GET_BONE_DESC 7

// sets the angle for a given bone (see struct AngleInfo)
#define PROTO_SET_BONE_ANGLE 8

// sets the length for a given bone (see struct LengthInfo)
#define PROTO_SET_BONE_LENGTH 9

#endif /* PROTO_H */
