/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef PRIVATE_CORE_BUILTIN_H_INCLUDED
#define PRIVATE_CORE_BUILTIN_H_INCLUDED

#include <sys/stat.h>
#include "core.h"

bool_t is_abs_path(string_t const *cmd);
bool_t is_a_path(string_t const *cmd);
string_t *find_in_path(string_t const *file, struct stat *fs);
char **to_cargs(string_t const *cmd, list_t *args);
int exec_try(string_t const *cmd, list_t *args);

#endif
