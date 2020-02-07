/*
** EPITECH PROJECT, 2019
** Mon titre 
** File description:
** Description 
*/
#ifndef IS_CHAINED_LIST_H_INCLUDED
#define IS_CHAINED_LIST_H_INCLUDED

#include "common_types.h"
#include "iterator.h"

extern const meta_bundle_t MB_INT;
extern const meta_bundle_t MB_FLOAT;
extern const meta_bundle_t MB_DOUBLE;
extern const meta_bundle_t MB_CHAR;
extern const meta_bundle_t MB_PTR;
extern const meta_bundle_t MB_BOOL;

typedef struct List {
    unsigned int size;
    iterator_t *begin;
    iterator_t *end;
    meta_bundle_t type_meta;
} list_t;

list_t *list_create(meta_bundle_t);
list_t *list_copy(list_t *list);
void list_merge(list_t *lhs, list_t *rhs);
iterator_t *list_get_begin(list_t *list);
iterator_t *list_get_end(list_t *list);
iterator_t list_begin(list_t *list);
iterator_t list_end(list_t *list);
bool_t list_final(list_t *list, iterator_t it);
bool_t list_start(list_t *list, iterator_t it);
unsigned int list_len(list_t const *list);
void *list_data(iterator_t it);
void list_push_back(list_t *list, void *data);
void list_push_front(list_t *list, void *data);
void list_pop_back(list_t *list);
void list_pop_front(list_t *list);
void *list_pull(list_t *list, iterator_t it);
void list_iswap(iterator_t *lhs, iterator_t *rhs);
list_t *list_splice(list_t *list, iterator_t begin, iterator_t end);
void list_revert(list_t *list);
void list_free(list_t **plist);
void **list_to_array(list_t *list);

#endif
