/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "nfa_node.h"

const meta_bundle_t MB_NFA_NODE = {
    nfa_copy,
    nfa_destroy,
    sizeof(nfa_node_t)
};

nfa_node_t *nfa_create(char const *set, nfa_options_t opt)
{
    nfa_node_t *nnode = malloc(sizeof(nfa_node_t));
    int slen = 0;

    if (set != 0)
        for (slen = 0; set[slen] != 0; slen++);
    if (slen == 0)
        nnode->entry_set = 0;
    else
        nnode->entry_set = (char*)mem_copy(set, sizeof(char) * (slen + 1));
    nnode->out_list = list_create(MB_NFA_NODE);
    nnode->options = opt;
    nnode->groups = malloc(sizeof(int) * 2);
    nnode->groups[0] = 2;
    nnode->groups[1] = 0;
    return (nnode);
}

void nfa_set_options(nfa_node_t *node, nfa_options_t opt)
{
    if (node == 0)
        return;
    node->options = opt;
}

int const *nfa_groups(nfa_node_t const *node)
{
    if (node == 0)
        return (0);
    return (node->groups);
}

void nfa_set_groups(nfa_node_t *node, int const* const glist)
{
    int *groups = 0;
    iterator_t it;

    if (node == 0 || glist == 0)
        return;
    if (node->groups != 0)
        free(node->groups);
    groups = malloc(sizeof(int) * glist[0]);
    for (int i = 0; i < glist[0]; i++) {
        groups[i] = glist[i];
    }
    node->groups = groups;
}

bool_t nfa_accepts(nfa_node_t *node, char c)
{
    if (node == 0)
        return (FALSE);
    if (node->entry_set == 0)
        return (TRUE);
    for (char const *ch = node->entry_set; *ch != 0; ch++)
        if (*ch == c)
            return (TRUE);
    return (FALSE);
}

bool_t nfa_final(nfa_node_t *node)
{
    return (node->options & NFA_FINAL);
}

bool_t nfa_looped(nfa_node_t *node)
{
    return (node->options & NFA_LOOPED);
}

nfa_node_t *nfa_link(nfa_node_t *lhs, nfa_node_t *rhs)
{
    iterator_t item;

    if (lhs == 0 || rhs == 0)
        return (0);
    list_push_back(lhs->out_list, rhs);
    item = it_back(list_end(lhs->out_list));
    return (nfa_node_t*)list_data(item);
}

list_t *nfa_advance(nfa_node_t *node, char c)
{
    list_t *list = 0;
    list_t *out = 0;
    iterator_t it;
    nfa_node_t *data = 0;
    bool_t accepted = FALSE;

    if (node == 0)
        return (0);
    list = node->out_list;
    for (it = list_begin(list); !list_final(list, it); it = it_next(it)) {
        data = (nfa_node_t*)list_data(it);
        if (nfa_accepts(data, c)) {
            out = (out == 0) ? list_create(MB_NFA_NODE) : out;
            list_push_front(out, data);
            accepted = TRUE;
        }
    }
    if (!accepted && nfa_looped(node) && nfa_accepts(node, c)) {
        out = (out == 0) ? list_create(MB_NFA_NODE) : out;
        list_push_front(out, node);
    }
    return (out);
}

void nfa_free(nfa_node_t **node)
{
    if ((*node)->entry_set != 0)
        free((*node)->entry_set);
    if ((*node)->out_list != 0)
        list_free(&(*node)->out_list);
    if ((*node)->groups != 0)
        free((*node)->groups);
    free(*node);
    *node = 0;
}

void *nfa_copy(void const *data)
{
    nfa_node_t *node = (nfa_node_t*)data;
    nfa_node_t *nnode = 0;
    int *groups;
    int len = 0;

    if (node == 0)
        return (0);
    if (node->entry_set != 0)
        for (len = 0; node->entry_set[len] != 0; len++);
    nnode = malloc(sizeof(nfa_node_t));
    if (len == 0)
        nnode->entry_set = 0;
    else
        nnode->entry_set = mem_copy(node->entry_set, sizeof(char) * (len + 1));
    nnode->out_list = list_copy(node->out_list);
    nnode->options = node->options;
    groups = node->groups;
    groups = (groups == 0) ? 0 : mem_copy(groups, sizeof(int) * groups[0]);
    nnode->groups = groups;
    return (nnode);
}

void nfa_destroy(void *data)
{
    nfa_node_t *node = (nfa_node_t*)data;

    if (node == 0)
        return;
    nfa_free(&node);
}
