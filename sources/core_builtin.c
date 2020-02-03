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

uint_t exec_builtin_cd(string_t const *command)
{
    string_t *arg = 0;
    list_t *arg_list = 0;
    bool_t matched = FALSE;
    int res = 0;

    if (command == 0)
        return (84);
    arg_list = get_args_if_matched(command, bi_cd_pattern(), &matched);
    res = (arg_list == 0 && matched) ? change_sdir(get_envvar("HOME")) : res;
    if (matched && arg_list != 0) {
        if (list_len(arg_list) == 1) {
            arg = (string_t*)list_data(list_begin(arg_list));
            res = change_dir(str_cstr(arg));
        } else {
            print_cerr("cd", "Too many arguments");
            res = 84;
        }
    }
    list_free(&arg_list);
    return (res);
}

uint_t exec_builtin_exit(string_t const *command)
{
    list_t *arg_list = 0;
    uint_t res = 0;
    bool_t matched = FALSE;

    if (command == 0)
        return (84);
    arg_list = get_args_if_matched(command, bi_exit_pattern(), &matched);
    if (arg_list != 0) {
        print_cerr("exit", "Invalid Syntax");
        res = 84;
    }
    if (arg_list == 0 && matched) {
        print_cchar("exit\n");
        res = 200;
    }
    list_free(&arg_list);
    return (res);
}

uint_t exec_builtin_env(string_t const *command)
{
    list_t *arg_list = 0;
    uint_t res = 0;
    bool_t matched = FALSE;

    if (command == 0)
        return (84);
    arg_list = get_args_if_matched(command, bi_env_pattern(), &matched);
    if (matched && arg_list == 0)
        print_env();
    else
        res = 84;
    list_free(&arg_list);
    return (res);
}

uint_t exec_builtin_setenv(string_t const *command)
{
    uint_t res = 0;
    bool_t matched = FALSE;
    list_t *arg_list = 0;
    string_t *key = 0;
    string_t *value = 0;

    arg_list = get_args_if_matched(command, bi_setenv_pattern(), &matched);
    if (matched && arg_list != 0 && list_len(arg_list) < 3) {
        key = (string_t*)list_data(list_begin(arg_list));
        if (list_len(arg_list) > 1)
            value = (string_t*)list_data(it_next(list_begin(arg_list)));
        else
            value = str_create("");
        set_envvar(str_cstr(key), str_cstr(value));
    } else if (matched && arg_list != 0 && list_len(arg_list) < 3) {
        print_cerr("setenv", "Too many arguments");
    } else if (matched)
        print_env();
    list_free(&arg_list);
    return (res);
}
