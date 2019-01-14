
#ifndef TYPES_H
#define TYPES_H

#ifdef __linux__

#include <sys/types.h>
typedef u_int16_t ushort;

#elif defined WIN32

#include <stdint.h>
typedef uint16_t ushort;

#endif

#endif /* TYPES_H */
