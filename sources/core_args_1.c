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
    list_t *args = str_split(argline, ' ');
    string_t *str = NULL;
    map_t *match = map_create(5, MB_STR);
    uint_t asize = list_len(args);

    if (argline == NULL)
        return (NULL);
    for (uint_t i = 0; i < asize; i++) {
        str_free(&str);
        str = list_pull(args, list_begin(args));
        if (str == NULL || str_len(str) < 1)
            continue;
        if (regex_extract(str_cstr(str), REGEX_CMD_ARG, match) == FALSE)
            continue;
        str = map_get(match, 1);
        str = (str == NULL) ? map_get(match, 2) : str;
        list_push_back(args, str);
        str = NULL;
    }
    return (map_free(&match), args);
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

    if (prompt == 0)
        return (84);
    cmds = extract_all_cmds(prompt);
    while (list_len(cmds) > 0) {
        cmd = list_pull(cmds, list_begin(cmds));
        if (cmd == NULL)
            continue;
        res = execute_list_cmd(cmd);
        free(cmd);
    }
    return (list_free(&cmds), res);
}
