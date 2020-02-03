/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "core.h"
#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

list_t *get_args_if_matched(string_t const *cmd, nfa_node_t *pat, bool_t *flag)
{
    map_t *matched = 0;
    list_t *arg_list = 0;

    if (cmd == 0 || pat == 0)
        return (0);
    matched = match(str_cstr(cmd), pat);
    if (flag != 0)
        *flag = (matched == 0) ? FALSE : TRUE;
    arg_list = str_split(map_get(matched, 1), ' ');
    map_free(&matched);
    nfa_free(&pat);
    return (arg_list);
}

uint_t exec_command(string_t const *command, string_t const *path)
{
    exec_builtin_cd(command);
    exec_builtin_env(command);
    exec_builtin_setenv(command);
    if (exec_builtin_exit(command) == 200)
        return (200);
    return (0);
}
