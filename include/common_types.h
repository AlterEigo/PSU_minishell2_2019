/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_COMMON_TYPES_H_INCLUDED
#define IS_COMMON_TYPES_H_INCLUDED

#include "curses.h"

typedef bool (bool_t);
typedef unsigned int (uint_t);
typedef unsigned long long (hash_value_t);
typedef long unsigned int (dsize_t);
typedef unsigned char (byte_t);
typedef char const* (cchar_t);
typedef void *(*cpy_constructor_ft)(void const*);
typedef void (*destructor_ft)(void*);

typedef struct MetaBundle {
    cpy_constructor_ft copy;
    destructor_ft destroy;
    dsize_t data_size;
} meta_bundle_t;

void *mem_copy(void const *data, dsize_t size);

#endif
