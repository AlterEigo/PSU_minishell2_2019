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
#include <signal.h>
#include <sys/wait.h>

#include "core.h"
#include "p_core_builtin.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "istl/utility.h"

const fnode_t MS_VAL[] = {
    {.cset = RC_WILD, .ps = 0, .ns = -1, .fs = FALSE, .gwl = 0, .gwr = 0},
    {.cset = CSET_ANUM, .ps = 0, .ns = 1, .fs = TRUE, .gwl = 1, .gwr = 2},
    {.cset = "0123456789", .ps = 0, .ns = -1, .fs = FALSE, .gwl = 0, .gwr = 0},
    {.cset = "_", .ps = 0, .ns = 1, .fs = TRUE, .gwl = 1, .gwr = 2},
    {.cset = CSET_ANUM, .ps = 1, .ns = 1, .fs = TRUE, .gwl = 1, .gwr = 2},
    {.cset = "_", .ps = 1, .ns = 1, .fs = TRUE, .gwl = 1, .gwr = 2},
    FNODE_NULL
};

int builtin_cd(list_t *args)
{
    int res = 0;
    string_t *arg = 0;
    string_t *var = 0;

    if (args == 0 || list_len(args) == 0) {
        var = get_envvar("HOME");
        if (var == 0)
            print_cerr("cd", "No such file or directory");
        res = change_sdir(var);
        str_free(&var);
    } else if (list_len(args) == 1) {
        arg = it_data(list_begin(args));
        if (str_cmp(arg, str_wcreate("-")) == TRUE)
            arg = get_envvar("OLDPWD");
        res = change_sdir(arg);
    } else {
        print_cerr("cd", "Too many arguments");
        res = 84;
    }
    return (res);
}

int builtin_exit(list_t *args)
{
    int res = 0;

    if (args == 0 || list_len(args) == 0)
        res = 200;
    else
        res = 12;
    if (isatty(0))
        write(1, "exit\n", 6);
    return (res);
}

int builtin_env(list_t *args)
{
    int res = 0;

    if (args == 0 || list_len(args) == 0) {
        print_env();
    } else {
        res = 84;
        print_cerr("env", "Too many arguments");
    }
    return (res);
}

int builtin_setenv(list_t *args)
{
    int res = 0;
    string_t *key = 0;
    string_t *value = 0;

    if (args == 0 || list_len(args) == 0)
        return (print_env(), 0);
    else if (list_len(args) > 2)
        return (print_cerr("setenv", "Too many arguments"), 84);
    key = it_data(list_begin(args));
    if (regex_extract(str_cstr(key), MS_VAL, NULL) != TRUE) {
        if (str_contains("0123456789", str_cstr(key)[0]))
            print_cerr("setenv", "Variable name must begin with a letter");
        else
            print_cerr("setenv", SETENV_ERR_1);
        return (1);
    }
    value = it_data(it_next(list_begin(args)));
    set_envvar(str_cstr(key), str_cstr(value));
    return (res);
}

int builtin_unsetenv(list_t *args)
{
    int res = 0;
    string_t *key = 0;

    if (args == 0 || list_len(args) == 0) {
        res = 1;
        print_cerr("unsetenv", "Too few arguments");
    } else if (list_len(args) > 1) {
        res = 1;
        print_cerr("unsetenv", "Too many arguments");
    } else {
        key = (string_t *)list_data(list_begin(args));
        unset_envvar(str_cstr(key));
    }
    return (res);
}
