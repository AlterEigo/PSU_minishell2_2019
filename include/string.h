/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_STRING_H_INCLUDED
#define IS_STRING_H_INCLUDED

#include "common_types.h"

typedef struct String {
    char *cstr;
    uint_t length;
} string_t;

extern const meta_bundle_t MB_STR;
void *str_copy(void const *str);
void str_destroy(void *str);

string_t *str_create(const cchar_t cstr);
string_t *str_wcreate(char *cstr);
void str_free(string_t **str);
cchar_t str_cstr(string_t const *str);
string_t *str_dup(string_t const *str);
string_t *str_concat(string_t const *lhs, string_t const *rhs);
string_t *str_addch(string_t const *lhs, char rhs);
uint_t str_len(string_t const *str);

#endif
