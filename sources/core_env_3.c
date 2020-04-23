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
        found = list_pull(env->keys, it);
        str_free(&found);
    }
    str_free(&key);
}
