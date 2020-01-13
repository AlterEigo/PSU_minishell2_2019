/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_ITERATOR_H_INCLUDED
#define IS_ITERATOR_H_INCLUDED

#include "common_types.h"

/*
** Iterator
** Wanted client code:
iterator_t it = list_begin(list);
while (it) {
    data = (type_t*)list_get_data(it);
    it = it_next(it);
}

iterator_t it = map_begin(map);
while (!it_eq(it, map_end(map))) {
    key = map_key(it);
    value = map_value(it);
}
*/
typedef struct Iterator {
    void *data;
    int layer_id;
    unsigned int data_size;
    unsigned long long hash;
    struct Iterator *next;
    struct Iterator *prior;
} iterator_t;

iterator_t it_create(void *data, unsigned int sizeof_data);
iterator_t *it_allocate(void *data, unsigned int sizeof_data);
bool_t it_eq(iterator_t lhs, iterator_t rhs);
bool_t it_has_next(iterator_t it);
bool_t it_has_prior(iterator_t it);
bool_t it_reach(iterator_t lhs, iterator_t rhs);
iterator_t it_next(iterator_t it);
iterator_t it_back(iterator_t it);
iterator_t *it_get_next(iterator_t *it);
iterator_t *it_get_prior(iterator_t *it);
void it_set_next(iterator_t *lhs, iterator_t *rhs);
void it_set_prior(iterator_t *lhs, iterator_t *rhs);
void it_couple(iterator_t *lhs, iterator_t *rhs);
void it_swap(iterator_t *lhs, iterator_t *rhs);
long long int it_distance(iterator_t lhs, iterator_t rhs);
iterator_t it_advance(iterator_t it, int rhs);
void *it_data(iterator_t it); 
void it_free(iterator_t **it);

#endif
