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

#include "istl/utility.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "command_model.h"
#include "core.h"

#include "./core_args_static_1.c"
#include "./core_args_static_2.c"

builtin_ft get_builtin(string_t const *command)
{
    hash_value_t chash;
    hash_value_t *harray = get_hash_array();
    builtin_ft *farray = get_builtin_array();

    if (command == 0)
        return (0);
    chash = hash_str(str_cstr(command));
    return (h_to_b(chash, harray, farray));
}

list_t *extract_all_args(string_t const *argline)
{
    list_t *list = list_create(MB_STR);
    map_t *match = map_create(5, MB_STR);
    string_t *str = NULL;

    if (argline == NULL)
        return (list_free(&list), map_free(&match), NULL);
    while (regex_extract(str_cstr(argline), REGEX_CMD_ARG, match) != FALSE) {
        str = map_get(match, 1);
        if (str == NULL)
            str = map_get(match, 2);
        list_push_back(list, str);
        argline = map_get(match, 3);
    }
    map_free(&match);
    return (list);
}

list_t *extract_all_cmds(string_t const *prompt)
{
    list_t *list = list_create((mdata_t) {0, 0, sizeof(cmd_t)});
    map_t *match = map_create(5, MB_STR);
    string_t *str = NULL;
    cmd_t cmd;

    if (prompt == NULL)
        return (list_free(&list), map_free(&match), NULL);
    while (regex_extract(str_cstr(prompt), REGEX_CMD, match) != FALSE) {
        cmd.name = map_get(match, 1);
        str = map_get(match, 2);
        str_replace(str, '\t', ' ');
        cmd.args = extract_all_args(str);
        cmd.op = map_get(match, 3);
        list_push_back(list, &cmd);
        prompt = map_get(match, 4);
        map_drop(match);
    }
    return (list);
}

int eval_prompt(string_t const *prompt)
{
    list_t *cmds = NULL;
    int res = 0;
    cmd_t *cmd = NULL;
    cmd_t *texas_oil = NULL;

    if (prompt == 0)
        return (84);
    cmds = extract_all_cmds(prompt);
    while (list_len(cmds) > 0) {
        cmd = list_pull(cmds, list_begin(cmds));
        if (cmd == NULL)
            continue;
        res = execute_list_cmd(cmd, texas_oil);
        print_fault_msg(res);
        if (texas_oil != NULL)
            free(texas_oil);
        texas_oil = cmd_is_piped(cmd) ? cmd : NULL;
    }
    return (list_free(&cmds), res);
}
