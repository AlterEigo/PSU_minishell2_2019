/*
** EPITECH PROJECT, 2019
** minishell1 main
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

string_t *get_cwd()
{
    char *buffer = 0;
    size_t b_size = 512;
    string_t *cwd = 0;

    buffer = malloc(sizeof(char) * b_size);
    if (getcwd(buffer, b_size) == 0) {
        if (buffer != 0)
            free(buffer);
        return (0);
    }
    cwd = str_wcreate(buffer);
    return (cwd);
}

map_t *env_to_map(char **envp)
{
    list_t *vars = 0;
    map_t *envm = 0;
    string_t *key = 0;
    string_t *value = 0;

    if (envp == 0)
        return (0);
    envm = map_create(10, MB_STR);
    for (uint_t i = 0; envp[i] != 0; i++) {
        value = str_create(envp[i]);
        vars = str_nsplit(value, '=', 1);
        str_free(&value);
        key = (string_t*)list_data(list_begin(vars));
        value = (string_t*)list_data(it_next(list_begin(vars)));
        map_insert(envm, hash_str(str_cstr(key)), value);
        list_free(&vars);
    }
    return (envm);
}

void print_env()
{
    char **envp = 0;

    env_manager(GETCENV, 0, &envp);
    for (uint_t i = 0; envp[i] != 0; i++) {
        print_cchar(envp[i]);
        write(1, "\n", 1);
    }
}

map_t *env_manager(env_option_t opt, char **environment, char ***penv)
{
    static map_t *envm = 0;
    static char **cenv = 0;

    if (opt == GETENV)
        return (envm);
    switch (opt) {
        case SETENV:
            cenv = environment;
            envm = env_to_map(cenv);
        break;
        case GETCENV:
            *penv = cenv;
        break;
        default:
        case GETENV:
            return (envm);
    }
    return (0);
}

string_t *get_envvar(cchar_t var)
{
    map_t *environment = 0;
    string_t *str = 0;

    if (var == 0)
        return (0);
    environment = env_manager(GETENV, 0, 0);
    str = (string_t*)map_get(environment, hash_str(var));
    str = str_create(str_cstr(str));
    return (str);
}

uint_t set_envvar(cchar_t var, cchar_t value)
{
    string_t *cvar = 0;
    map_t *environment = 0;

    if (var == 0)
        return (84);
    environment = env_manager(GETENV, 0, 0);
    cvar = (string_t*)map_pull(environment, hash_str(var));
    str_free(&cvar);
    cvar = str_create(value);
    map_insert(environment, hash_str(var), cvar);
    str_free(&cvar);
    return (0);
}
