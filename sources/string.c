/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include <unistd.h>
#include "string.h"

const meta_bundle_t MB_STR = {
    str_copy,
    str_destroy,
    sizeof(string_t)
};

void *str_copy(void const *str)
{
    string_t *nstr = 0;

    if (str == 0)
        return (0);
    nstr = (string_t*)str;
    nstr = str_dup(nstr);
    return (nstr);
}

void str_print(string_t const *str)
{
    uint_t len;
    char const *cstr = 0;

    cstr = str_cstr(str);
    len = str_len(str);
    write(1, cstr, len);
}

void str_errprint(string_t const *str)
{
    uint_t len;
    char const *cstr = 0;

    cstr = str_cstr(str);
    len = str_len(str);
    write(2, cstr, len);
}

void str_destroy(void *data)
{
    string_t *str = (string_t*)data;

    if (str == 0)
        return;
    str_free(&str);
}

string_t *str_create(const cchar_t cstr)
{
    string_t *nstr = malloc(sizeof(string_t));
    uint_t len = 0;

    nstr->cstr = 0;
    if (cstr != 0) {
        for (len = 0; cstr[len] != 0; len++);
        nstr->cstr = (char*)mem_copy(cstr, len + 1);
    }
    nstr->length = len;
    return (nstr);
}

string_t *str_wcreate(char *cstr)
{
    string_t *nstr = malloc(sizeof(string_t));
    uint_t len = 0;

    if (cstr != 0)
        for (len = 0; cstr[len] != 0; len++);
    nstr->cstr = cstr;
    nstr->length = len;
    return (nstr);
}

void str_free(string_t **pstr)
{
    string_t *str = 0;

    if (pstr == 0 || *pstr == 0)
        return;
    str = *pstr;
    if (str->cstr != 0)
        free(str->cstr);
    free(str);
    *pstr = 0;
}

cchar_t str_cstr(string_t const *str)
{
    return (cchar_t)(str->cstr);
}

string_t *str_dup(string_t const *str)
{
    string_t *nstr = 0;

    if (str == 0)
        return (0);
    nstr = str_create(str_cstr(str));
    return (nstr);
}

static uint_t max_len(uint_t lhs, uint_t rhs)
{
    return ((lhs > rhs) ? lhs : rhs);
}

string_t *str_concat(string_t const *lhs, string_t const *rhs)
{
    uint_t len1;
    uint_t len2;
    char *ncstr = 0;
    uint_t cr = 0;

    if (lhs == 0 && rhs == 0)
        return (0);
    len1 = (lhs == 0) ? 0 : str_len(lhs);
    len2 = (rhs == 0) ? 0 : str_len(rhs);
    ncstr = malloc(sizeof(char) * (len1 + len2 + 1));
    for (uint_t i = 0; i < max_len(len1, len2); i++, cr++) {
        if (i < len1)
            ncstr[cr] = str_cstr(lhs)[i];
        if (i < len2)
            ncstr[cr + len1] = str_cstr(rhs)[i];
    }
    ncstr[len1 + len2] = 0;
    return (str_wcreate(ncstr));
}

string_t *str_substr(string_t const *lhs, uint_t start, uint_t end)
{
    uint_t len;

    if (lhs == 0)
        return (0);
    len = str_len(lhs);
    return (0);
}

string_t *str_addch(string_t const *lhs, char rhs)
{
    char *tmp = 0;
    string_t *nstr = 0;
    string_t *ret = 0;

    tmp = malloc(sizeof(char) * 2);
    tmp[0] = rhs;
    tmp[1] = 0;
    nstr = str_wcreate(tmp);
    ret = str_concat(lhs, nstr);
    str_free(&nstr);
    return (ret);
}

uint_t str_len(string_t const *str)
{
    return (str->length);
}

bool_t str_ccmp(string_t const *lhs, cchar_t rhs)
{
    string_t *s_rhs = 0;
    bool_t res = FALSE;

    s_rhs = str_create(rhs);
    res = str_cmp(lhs, s_rhs);
    str_free(&s_rhs);
    return (res);
}

bool_t str_cmp(string_t const *lhs, string_t *rhs)
{
    uint_t len = 0;

    if (lhs == 0) {
        if (rhs == 0)
            return (TRUE);
        return (FALSE);
    }
    if (str_len(lhs) != str_len(rhs))
        return (FALSE);
    len = str_len(lhs);
    for (uint_t i = 0; i < len; i++) {
        if (str_cstr(lhs)[i] != str_cstr(rhs)[i])
            return (FALSE);
    }
    return (TRUE);
}
