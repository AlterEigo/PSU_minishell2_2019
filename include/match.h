/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_MATCH_H_INCLUDED
#define IS_MATCH_H_INCLUDED

#include "common_types.h"
#include "hash_table.h"
#include "nfa_node.h"

map_t *match(char const *str, nfa_node_t *pattern);

#endif
