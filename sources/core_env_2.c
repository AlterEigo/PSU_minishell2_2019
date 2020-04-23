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

#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "istl/common_types.h"
#include "core.h"
#include "p_core_env.h"
#include "env_map.h"

void print_env(void)
{
    env_map_t *env = env_manager(GETENV, 0);
    iterator_t it;
    string_t *key = 0;
    string_t *value = 0;

    if (env == 0)
        return;
    it = list_begin(env->keys);
    for (uint_t i = 0; i < list_len(env->keys); i++, it = it_next(it)) {
        key = (string_t *)list_data(it);
        value = get_envvar(str_cstr(key));
        print_cchar(str_cstr(key));
        write(1, "=", 1);
        if (value != 0)
            print_cchar(str_cstr(value));
        str_free(&value);
        write(1, "\n", 1);
    }
}

env_map_t *env_manager(env_option_t opt, char **environment)
{
    static env_map_t env_map;

    if (opt == SETENV) {
        env_map = env_to_map(environment);
    } else if (opt == FREE) {
        map_free(&env_map.val_map);
        list_free(&env_map.keys);
    } else {
        return (&env_map);
    }
    return (0);
}

string_t *get_envvar(cchar_t var)
{
    map_t *environment = 0;
    string_t *str = 0;

    if (var == 0)
        return (0);
    environment = env_manager(GETENV, 0)->val_map;
    str = (string_t *)map_get(environment, hash_str(var));
    str = (str == 0) ? 0 : str_create(str_cstr(str));
    return (str);
}

uint_t set_envvar(cchar_t var, cchar_t value)
{
    string_t *cvar = 0;
    map_t *environment = 0;

    if (var == 0)
        return (84);
    environment = env_manager(GETENV, 0)->val_map;
    env_add_key(var);
    cvar = (string_t *)map_pull(environment, hash_str(var));
    str_free(&cvar);
    cvar = (value == 0) ? str_create("") : str_create(value);
    map_insert(environment, hash_str(var), cvar);
    str_free(&cvar);
    return (0);
}

uint_t unset_envvar(cchar_t var)
{
    string_t *cvar = 0;
    env_map_t *environment = 0;
    iterator_t it;

    if (var == 0)
        return (84);
    environment = env_manager(GETENV, 0);
    cvar = str_create(var);
    it = env_key_exists(cvar);
    str_free(&cvar);
    if (!list_final(environment->keys, it)) {
        cvar = (string_t *)list_pull(environment->keys, it);
        str_free(&cvar);
        cvar = (string_t *)map_pull(environment->val_map, hash_str(var));
        str_free(&cvar);
    }
    return (0);
}
