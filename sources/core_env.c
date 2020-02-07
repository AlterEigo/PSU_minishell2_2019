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
#include "env_map.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

static iterator_t env_key_exists(string_t const *key)
{
    env_map_t *env = env_manager(GETENV, 0);
    string_t *cur = 0;
    iterator_t it;

    if (key == 0)
        return (list_end(env->keys));
    it = list_begin(env->keys);
    for (uint_t i = 0; i < list_len(env->keys); i++, it = it_next(it)) {
        cur = (string_t*)list_data(it);
        if (str_cmp(cur, key) == TRUE)
            return (it);
    }
    return (list_end(env->keys));
}

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

env_map_t env_to_map(char **envp)
{
    env_map_t env_map;
    list_t *vars = 0;
    string_t *key = 0;
    string_t *value = 0;

    env_map.keys = list_create(MB_STR);
    env_map.val_map = map_create(10, MB_STR);
    for (uint_t i = 0; envp[i] != 0; i++) {
        value = str_create(envp[i]);
        vars = str_nsplit(value, '=', 1);
        str_free(&value);
        key = (string_t*)list_data(list_begin(vars));
        value = (string_t*)list_data(it_next(list_begin(vars)));
        list_push_back(env_map.keys, key);
        map_insert(env_map.val_map, hash_str(str_cstr(key)), value);
        list_free(&vars);
    }
    return (env_map);
}

void print_env()
{
    env_map_t *env = env_manager(GETENV, 0);
    iterator_t it;
    string_t *key = 0;
    string_t *value = 0;

    if (env == 0)
        return;
    it = list_begin(env->keys);
    for (uint_t i = 0; i < list_len(env->keys); i++, it = it_next(it)) {
        key = (string_t*)list_data(it);
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
    str = (string_t*)map_get(environment, hash_str(var));
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
    cvar = (string_t*)map_pull(environment, hash_str(var));
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
    if (!list_final(environment->keys, it)) {
	cvar = (string_t*)list_pull(environment->keys, it);
	str_free(&cvar);
	cvar = (string_t*)map_pull(environment->val_map, hash_str(var));
	str_free(&cvar);
    }
    return (0);
}

void env_add_key(cchar_t ckey)
{
    env_map_t *env = env_manager(GETENV, 0);
    iterator_t it;
    string_t *key = 0;

    if (ckey == 0)
        return;
    key = str_create(ckey);
    it = env_key_exists(key);
    if (list_final(env->keys, it))
        list_push_back(env->keys, key);
    str_free(&key);
}

void env_rem_key(cchar_t ckey)
{
    env_map_t *env = env_manager(GETENV, 0);
    string_t *found = 0;
    iterator_t it;
    string_t *key = str_create(ckey);

    it = env_key_exists(key);
    if (!list_final(env->keys, it)) {
        found = list_pull(env->keys, it);;
        str_free(&found);
    }
    str_free(&key);
}
