/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef BUILTIN_PATTERN_H_INCLUDED
#define BUILTIN_PATTERN_H_INCLUDED

#include "common_types.h"
#include "nfa_node.h"

typedef struct NodeOpt {
    char const *charset;
    nfa_options_t opt;
    int const *groups;
    int link;
} node_opt_t;

nfa_node_t *bi_command_pattern();

#endif
