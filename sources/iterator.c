/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "iterator.h"

static unsigned long long get_unique_id()
{
    static unsigned long long id = 0;

    return (id++);
}

iterator_t it_create(void *data, unsigned int sizeof_data)
{
    unsigned long long id = get_unique_id();
    iterator_t it;

    it.data = data;
    it.data_size = sizeof_data;
    it.hash = id;
    it.next = 0;
    it.prior = 0;
    it.layer_id = id;
    id += 1;
    return (it);
}

iterator_t *it_allocate(void *data, unsigned int sizeof_data)
{
    iterator_t *it = malloc(sizeof(iterator_t));

    *it = it_create(data, sizeof_data);
    return (it);
}

bool_t it_eq(iterator_t lhs, iterator_t rhs)
{
    if (lhs.hash == rhs.hash)
        return (TRUE);
    return (FALSE);
}

void *it_data(iterator_t it)
{
    return (it.data);
}

bool_t it_has_next(iterator_t it)
{
    if (it.next != 0)
        return (TRUE);
    return (FALSE);
}

bool_t it_has_prior(iterator_t it)
{
    if (it.prior != 0)
        return (TRUE);
    return (FALSE);
}

iterator_t it_next(iterator_t it)
{
    if (it.next != 0)
        return (*it.next);
    return (it);
}

iterator_t it_back(iterator_t it)
{
    if (it.prior != 0)
        return (*it.prior);
    return (it);
} 

iterator_t *it_get_next(iterator_t *it)
{
    return (it->next);
}

iterator_t *it_get_prior(iterator_t *it)
{
    return (it->prior);
}

void it_set_next(iterator_t *lhs, iterator_t *rhs)
{
    if (lhs == 0)
        return;
    lhs->next = rhs;
    if (rhs != 0)
        rhs->layer_id = lhs->layer_id;
}

void it_set_prior(iterator_t *lhs, iterator_t *rhs)
{
    if (lhs == 0)
        return;
    lhs->prior = rhs;
    if (rhs != 0)
        lhs->layer_id = rhs->layer_id;
}

void it_couple(iterator_t *lhs, iterator_t *rhs)
{
    if (lhs != 0)
        it_set_next(lhs, rhs);
    if (rhs != 0)
        it_set_prior(rhs, lhs);
}

void it_free(iterator_t **pit)
{
    iterator_t *it = *pit;

    free(it);
    *pit = 0;
}

void it_swap(iterator_t *lhs, iterator_t *rhs)
{
    if (lhs == 0 || rhs == 0)
        return;
    void *data = lhs->data;
    lhs->data = rhs->data;
    rhs->data = data;
}

bool_t it_reach(iterator_t lhs, iterator_t rhs)
{
    if (lhs.layer_id == rhs.layer_id)
        return (TRUE);
    return (FALSE);
}

long long int it_distance(iterator_t lhs, iterator_t rhs)
{
    long long int i = 0;
    iterator_t trh = lhs;

    if (!it_reach(lhs, rhs))
        return (0);
    while (!it_eq(lhs, rhs) && !it_eq(trh, rhs)) {
        lhs = it_next(lhs);
        trh = it_back(trh);
        i += 1;
    }
    return (i);
}
