/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_ENV_MAP_H_INCLUDED
#define IS_ENV_MAP_H_INCLUDED

#include "common_types.h"
#include "hash_table.h"

typedef struct EnvironmentMap {
    map_t *val_map;
    list_t *keys;
} env_map_t;

#endif
