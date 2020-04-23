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

iterator_t env_key_exists(string_t const *key)
{
    env_map_t *env = env_manager(GETENV, 0);
    string_t *cur = 0;
    iterator_t it;

    if (key == 0)
        return (list_end(env->keys));
    it = list_begin(env->keys);
    for (uint_t i = 0; i < list_len(env->keys); i++, it = it_next(it)) {
        cur = (string_t *)list_data(it);
        if (str_cmp(cur, key) == TRUE)
            return (it);
    }
    return (list_end(env->keys));
}

char **env_to_char(void)
{
    env_map_t *env = env_manager(GETENV, 0);
    iterator_t it;
    char **ret = malloc(sizeof(char *) * (list_len(env->keys) + 1));
    string_t *cur = 0;
    string_t *tmp = 0;

    it = list_begin(env->keys);
    for (uint_t i = 0; i < list_len(env->keys); it = it_next(it), i++) {
        cur = (string_t *)list_data(it);
        tmp = str_addch(cur, '=');
        cur = str_concat(tmp, map_get(env->val_map, hash_str(str_cstr(cur))));
        ret[i] = str_to_cstr(cur);
        str_free(&cur);
        str_free(&tmp);
    }
    ret[list_len(env->keys)] = 0;
    return (ret);
}

string_t *get_cwd(void)
{
    return (get_envvar("PWD"));
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
        key = (string_t *)list_data(list_begin(vars));
        value = (string_t *)list_data(it_next(list_begin(vars)));
        list_push_back(env_map.keys, key);
        map_insert(env_map.val_map, hash_str(str_cstr(key)), value);
        list_free(&vars);
    }
    return (env_map);
}
