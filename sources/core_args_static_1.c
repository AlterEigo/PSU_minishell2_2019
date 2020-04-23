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

static hash_value_t *get_hash_array(void)
{
    static hash_value_t harray[6] = {0};
    static bool init = FALSE;

    if (!init) {
        harray[0] = hash_str("cd");
        harray[1] = hash_str("exit");
        harray[2] = hash_str("env");
        harray[3] = hash_str("setenv");
        harray[4] = hash_str("unsetenv");
        init = TRUE;
    }
    return (harray);
}

static builtin_ft *get_builtin_array(void)
{
    static builtin_ft farray[6] = {0};
    static bool init = FALSE;

    if (!init) {
        farray[0] = builtin_cd;
        farray[1] = builtin_exit;
        farray[2] = builtin_env;
        farray[3] = builtin_setenv;
        farray[4] = builtin_unsetenv;
        init = TRUE;
    }
    return (farray);
}

static string_t *interpret_cmd(string_t const *prompt, list_t **args)
{
    string_t *cmd = 0;
    string_t *tmp = NULL;
    list_t *cmds = NULL;

    cmds = extract_all_cmds(prompt);
    return (cmd);
}
