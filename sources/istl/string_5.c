/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include <unistd.h>
#include "istl/string.h"
#include "istl/utility.h"

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
