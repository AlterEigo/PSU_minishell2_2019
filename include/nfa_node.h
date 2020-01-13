/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_NFA_NODE_H_INCLUDED
#define IS_NFA_NODE_H_INCLUDED

#include "common_types.h"
#include "list.h"

typedef enum {
    NFA_DEFAULT = 0b00000000,
    NFA_FINAL = 0b00000001,
    NFA_LOOPED = 0b00000010
} nfa_options_t;

typedef struct NfaNode
{
    char *entry_set;
    list_t *out_list;
    nfa_options_t options;
    int *groups;
} nfa_node_t;

extern const meta_bundle_t MB_NFA_NODE;

nfa_node_t *nfa_create(char const *set, nfa_options_t);
bool_t nfa_accepts(nfa_node_t *node, char c);
list_t *nfa_advance(nfa_node_t *node, char c);
bool_t nfa_final(nfa_node_t *node);
bool_t nfa_looped(nfa_node_t *node);
int const *nfa_groups(nfa_node_t const *node);
void nfa_set_options(nfa_node_t *node, nfa_options_t);
void nfa_set_groups(nfa_node_t *node, const int[]);
nfa_node_t *nfa_link(nfa_node_t *lhs, nfa_node_t *rhs);
void nfa_free(nfa_node_t **node);
void *nfa_copy(void const *data);
void nfa_destroy(void *data);

#endif
