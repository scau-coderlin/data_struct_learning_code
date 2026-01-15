#ifndef TYPES_H
#define TYPES_H

typedef enum {
    OK,
    ERROR,
    EMPTY,
    FULL,
    OVERFLOW,
    SYSERR,
} Status;

typedef int ElemType;

#define bool    int
#define true    1
#define false   0

#endif