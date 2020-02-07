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

static builtin_ft h_to_b(hash_value_t hs, hash_value_t ha[], builtin_ft fa[])
{
    if (ha == 0 || fa == 0)
	return (0);
    for (int i = 0; ha[i] != 0; i++) {
	if (ha[i] == hs)
	    return (fa[i]);
    }
    return (0);
}

builtin_ft get_builtin(string_t const *command)
{
    hash_value_t chash;
    hash_value_t harray[6] = {0};
    builtin_ft farray[6] = {0};

    if (command == 0)
	return (0);
    chash = hash_str(str_cstr(command));
    harray[0] = hash_str("cd");
    harray[1] = hash_str("exit");
    harray[2] = hash_str("env");
    harray[3] = hash_str("setenv");
    harray[4] = hash_str("unsetenv");
    farray[0] = builtin_cd;
    farray[1] = builtin_exit;
    farray[2] = builtin_env;
    farray[3] = builtin_setenv;
    farray[4] = builtin_unsetenv;
    return (h_to_b(chash, harray, farray));
}

uint_t eval_prompt(string_t const *prompt)
{
    string_t *command = 0;
    list_t *args = 0;
    map_t *processed = 0;

    if (prompt == 0)
	return (84);
    processed = match(str_cstr(prompt), bi_command_pattern());
    command = (string_t*)map_get(processed, 1);
    args = str_split(map_get(processed, 2), ' ');
    return (200);
}

uint_t exec_command(string_t const *command, string_t const *path)
{
    exec_builtin_cd(command);
    exec_builtin_env(command);
    exec_builtin_setenv(command);
    exec_builtin_unsetenv(command);
    if (exec_builtin_exit(command) == 200)
        return (200);
    return (0);
}
