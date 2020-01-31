/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "builtin_pattern.h"

nfa_node_t *bi_cd_pattern()
{
    nfa_node_t *origin = nfa_create("c", NFA_DEFAULT);
    nfa_node_t *last = origin;
    nfa_node_t *nnode = 0;

    nfa_set_groups(origin, (int[]){2, 0});

    nnode = nfa_create("d", NFA_FINAL | NFA_DEFAULT);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(0, NFA_DEFAULT | NFA_LOOPED);
    nfa_set_groups(nnode, (int[]){2, 0});
    nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(" \n", NFA_FINAL);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(0, NFA_FINAL | NFA_LOOPED);
    nfa_set_groups(nnode, (int[]){3, 0, 1});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);
    return (origin);
}

nfa_node_t *bi_exit_pattern()
{
    nfa_node_t *origin = nfa_create("e", NFA_DEFAULT);
    nfa_node_t *last = origin;
    nfa_node_t *nnode = 0;

    nfa_set_groups(origin, (int[]){2, 0});

    nnode = nfa_create("x", NFA_DEFAULT);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create("i", NFA_DEFAULT);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create("t", NFA_FINAL);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(0, NFA_DEFAULT | NFA_LOOPED);
    nfa_set_groups(nnode, (int[]){2, 0});
    nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(" \n", NFA_FINAL);
    nfa_set_groups(nnode, (int[]){2, 0});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);

    nnode = nfa_create(0, NFA_FINAL | NFA_LOOPED);
    nfa_set_groups(nnode, (int[]){3, 0, 1});
    last = nfa_link(last, nnode);
    nfa_free(&nnode);
    return (origin);
}

nfa_node_t *bi_setenv_pattern()
{
    return (0);
}

nfa_node_t *bi_env_pattern()
{
    return (0);
}

nfa_node_t *bi_unsetenv_pattern()
{
    return (0);
}
