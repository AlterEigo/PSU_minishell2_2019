/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "match.h"
#include "list.h"
#include "string.h"

static bool_t at_least_one_final(list_t *nfa_list)
{
    iterator_t it;
    nfa_node_t *node = 0;
    bool_t res = FALSE;

    if (nfa_list == 0)
        return (FALSE);
    it = list_begin(nfa_list);
    while (!list_final(nfa_list, it)) {
        node = (nfa_node_t*)list_data(it);
        res = nfa_final(node) ? TRUE : res;
        it = it_next(it);
    }
    return (res);
}

static list_t *match_nodes(list_t *matched, char c)
{
    iterator_t it;
    nfa_node_t *node = 0;
    list_t *tmp = 0;
    list_t *res = FALSE;

    if (matched == 0)
        return (0);
    it = list_begin(matched);
    for (unsigned int i = 0; i < list_len(matched);i++, it = it_next(it)) {
        node = (nfa_node_t*)list_data(it);
        res = nfa_advance(node, c);
        if (res != 0) {
            tmp = (tmp == 0) ? list_create(MB_NFA_NODE) : tmp;
            list_merge(tmp, res);
            list_free(&res);
        }
    }
    return (tmp);
}

static char *str_addchar(char const *lhs, char rhs)
{
    int slen;
    char *nstr = 0;

    if (lhs == 0) {
        nstr = malloc(sizeof(char) * 2);
        nstr[0] = rhs;
        nstr[1] = 0;
        return (nstr);
    }
    for (slen = 0; lhs[slen] != 0; slen++);
    nstr = malloc(sizeof(char) * (slen + 2));
    nstr[slen] = rhs;
    nstr[slen + 1] = 0;
    for (int i = 0; i < slen; i++) {
        nstr[i] = lhs[i];
    }
    return (nstr);
}

static void fill_node_groups(nfa_node_t *node, char c, map_t *gmap, map_t *exc)
{
    int const *groups = 0;
    string_t *str = 0;
    string_t *tmp = 0;
    const bool_t val = TRUE;

    groups = nfa_groups(node);
    for (int j = 1; j < groups[0]; j++) {
        if (map_get(exc, groups[j]) == 0 && nfa_accepts(node, c)) {
            str = map_pull(gmap, groups[j]);
            tmp = str_addch(str, c);
            if (str != 0)
                str_free(&str);
            map_insert(gmap, groups[j], tmp);
            if (tmp != 0)
                str_free(&tmp);
            map_insert(exc, groups[j], &val);
        }
    }
}

static void extract_groups(list_t *nodes, map_t *gmap, char c)
{
    iterator_t it;
    nfa_node_t *node = 0;
    map_t *flags = 0;
    const bool_t val = TRUE;

    if (nodes == 0 || gmap == 0)
        return;
    flags = map_create(10, MB_BOOL);
    it = list_begin(nodes);
    for (int i = 0; i < (int)list_len(nodes); i++, it = it_next(it)) {
        node = (nfa_node_t*)list_data(it);
        fill_node_groups(node, c, gmap, flags);
    }
    map_free(&flags);
}

map_t *match(char const *str, nfa_node_t *pattern)
{
    list_t *matched = 0;
    list_t *tmp = 0;
    map_t *gmap = 0;
    map_t *res = 0;

    if (str == 0 || str[0] == 0 || pattern == 0)
        return (FALSE);
    gmap = map_create(10, MB_STR);
    matched = list_create(MB_NFA_NODE);
    if (nfa_accepts(pattern, str[0]))
        list_push_front(matched, pattern);
    extract_groups(matched, gmap, str[0]);
    for (char const *c = str + 1; *c != 0; c++) {
        tmp = match_nodes(matched, *c);
        extract_groups(tmp, gmap, *c);
        list_free(&matched);
        matched = tmp;
    }
    if (at_least_one_final(matched))
        res = gmap;
    else
        map_free(&gmap);
    list_free(&matched);
    return (res);
}
