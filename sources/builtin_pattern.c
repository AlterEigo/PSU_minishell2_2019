/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "builtin_pattern.h"

static nfa_node_t *create_expression(node_opt_t const *const opts, uint_t size)
{
    nfa_node_t **nodes = 0;
    nfa_node_t *node = 0;

    if (opts == 0)
        return (0);
    nodes = malloc(sizeof(nfa_node_t*) * size);
    for (uint_t i = 0; i < size; i++) {
        nodes[i] = nfa_create(opts[i].charset, opts[i].opt);
        nfa_set_groups(nodes[i], opts[i].groups);
    }
    for (int i = size - 1; i >= 0; i--) {
        if (opts[i].link < 0 || (uint_t)opts[i].link >= size)
            continue;
        node = nfa_link(nodes[opts[i].link], nodes[i]);
        nfa_free(&nodes[i]);
        nodes[i] = node;
    }
    node = nodes[0];
    free(nodes);
    return (node);
}

nfa_node_t *bi_command_pattern()
{
    node_opt_t opts[3];

    opts[0] = (node_opt_t){0, NFA_FINAL | NFA_LOOPED, (int[]){3, 0, 1}, -1};
    opts[1] = (node_opt_t){" \n", NFA_FINAL | NFA_LOOPED, (int[]){2, 0}, 0};
    opts[2] = (node_opt_t){0, NFA_FINAL | NFA_LOOPED, (int[]){3, 0, 2}, 1};
    return (create_expression(opts, 3));
}
