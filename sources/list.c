/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "list.h"

const meta_bundle_t MB_INT = {0, 0, sizeof(int)};
const meta_bundle_t MB_FLOAT = {0, 0, sizeof(float)};
const meta_bundle_t MB_DOUBLE = {0, 0, sizeof(double)};
const meta_bundle_t MB_CHAR = {0, 0, sizeof(char)};
const meta_bundle_t MB_PTR = {0, 0, sizeof(int*)};
const meta_bundle_t MB_BOOL = {0, 0, sizeof(bool_t)};

list_t *list_create(meta_bundle_t meta)
{
    list_t *list = malloc(sizeof(list_t));

    list->size = 0;
    list->begin = it_allocate(0, 0);
    list->end = list->begin;
    list->type_meta = meta;
    it_couple(list->begin, list->end);
    return (list);
}

void **list_to_array(list_t *list)
{
    unsigned int size;
    dsize_t dsize;
    void **array = 0;
    iterator_t it;

    if (list == 0 || list_len(list) < 1)
        return (0);
    it = list_begin(list);
    dsize = list->type_meta.data_size;
    size = list_len(list);
    array = (void**)malloc(sizeof(void*) * size);
    for (int i = 0; !list_final(list, it); i++) {
        if (list->type_meta.copy == 0)
            array[i] = mem_copy(list_data(it), dsize);
        else
            array[i] = list->type_meta.copy(list_data(it));
        it = it_next(it);
    }
    return (array);
}

list_t *list_copy(list_t *list)
{
    iterator_t begin;
    iterator_t end;
    list_t *nlist;

    if (list == 0)
        return (0);
    begin = list_begin(list);
    end = list_end(list);
    nlist = list_splice(list, begin, end);
    nlist->type_meta = list->type_meta;
    return (nlist);
}

void list_merge(list_t *lhs, list_t *rhs)
{
    iterator_t begin = list_begin(rhs);
    void *data = 0;

    for (iterator_t it = begin; !list_final(rhs, it); it = it_next(it))
        list_push_back(lhs, list_data(it));
}

void list_push_back(list_t *list, void *data)
{
    iterator_t *it = 0;
    dsize_t sizeof_data;
    cpy_constructor_ft copy;

    if (list == 0)
        return;
    copy = list->type_meta.copy;
    sizeof_data = list->type_meta.data_size;
    data = (copy == 0) ? mem_copy(data, sizeof_data) : copy(data);
    it = it_allocate(data, sizeof_data);
    if (list->size == 0) {
        list->begin = it;
        it_couple(list->begin, list->end);    
    } else {
        it_couple(it_get_prior(list->end), it);
        it_couple(it, list->end);
    }
    list->size += 1;
}

void list_push_front(list_t *list, void *data)
{
    iterator_t *it = 0;
    dsize_t sizeof_data;
    cpy_constructor_ft copy;

    if (list == 0)
        return;
    copy = list->type_meta.copy;
    sizeof_data = list->type_meta.data_size;
    data = (copy == 0) ? mem_copy(data, sizeof_data) : copy(data);
    it = it_allocate(data, sizeof_data);
    it->next = list->begin;
    list->begin->prior = it;
    it->layer_id = list->begin->layer_id;
    list->begin = it;
    list->size += 1;
}

void list_pop_back(list_t *list)
{
    iterator_t *prior = 0;
    iterator_t *it = 0;
    void *data = 0;

    if (list == 0 || list->size < 1)
        return;
    it = it_get_prior(list->end);
    prior = it_get_prior(it);
    it_couple(prior, list->end);
    data = list_data(*it);
    if (list->type_meta.destroy == 0)
        free(data);
    else
        list->type_meta.destroy(data);
    it_free(&it);
    list->size -= 1;
}

void list_pop_front(list_t *list)
{
    iterator_t *it = 0;
    iterator_t *next = 0;
    void *data = 0;

    if (list == 0 || list->size < 1)
        return;
    it = list->begin;
    next = it_get_next(it);
    it_couple(0, next);
    data = list_data(*it);
    if (list->type_meta.destroy == 0)
        free(data);
    else
        list->type_meta.destroy(data);
    it_free(&it);
    list->begin = next;
    list->size -= 1;
}

void *list_pull(list_t *list, iterator_t it)
{
    iterator_t *prior = 0;
    iterator_t *next = 0;
    iterator_t *pit = 0;
    void *data = 0;

    if (list == 0 || it_eq(it, list_end(list)))
        return (0);
    if (!it_reach(list_begin(list), it))
        return (0);
    data = it_data(it);
    prior = it_get_prior(&it);
    next = it_get_next(&it);
    if (prior == 0)
	list->begin = next;
    pit = (prior == 0) ? it_get_prior(next) : it_get_next(prior);
    it_free(&pit);
    it_couple(prior, next);
    list->size -= 1;
    return (data);
}

iterator_t *list_get_begin(list_t *list)
{
    if (list == 0)
        return (0);
    return (list->begin);
}

iterator_t *list_get_end(list_t *list)
{
    if (list == 0)
        return (0);
    return (list->end);
}

void *list_data(iterator_t it)
{
    return (it_data(it));
}

iterator_t list_begin(list_t *list)
{
    return (*list->begin);
}

iterator_t list_end(list_t *list)
{
    return (*list->end);
}

unsigned int list_len(list_t const *list)
{
    return (list->size);
}

void list_free(list_t **plist)
{
    list_t *list = *plist;
    iterator_t *it = list_get_begin(list);
    iterator_t *end = list_get_end(list);
    iterator_t *tmp = 0;
    void *data = 0;

    if (plist == 0 || *plist == 0)
        return;
    for (;it != end; it = tmp) {
        tmp = it_get_next(it);
        data = list_data(*it);
        if (list->type_meta.destroy == 0)
            free(data);
        else
            list->type_meta.destroy(data);
        it_free(&it);
    }
    it_free(&it);
    free(list);
    *plist = 0;
}

bool_t list_final(list_t *list, iterator_t it)
{
    return (it_eq(it, list_end(list)));
}

bool_t list_start(list_t *list, iterator_t it)
{
    return (it_eq(it, list_begin(list)));
}

list_t *list_splice(list_t *list, iterator_t begin, iterator_t end)
{
    list_t *nlist = 0;

    if (list == 0)
        return (0);
    nlist = list_create(list->type_meta);
    for (iterator_t it = begin; !it_eq(it, end); it = it_next(it))
        list_push_back(nlist, list_data(it));
    return (nlist);
}

void *mem_copy(void const *data, dsize_t size)
{
    void *ndata = malloc(size);
    byte_t *byte = (byte_t*)ndata;

    for (dsize_t i = 0; i < size; i++) {
        *(byte + i) = *((byte_t*)data + i);
    }
    return (ndata);
}

void list_revert(list_t *list)
{
    iterator_t it;
    list_t *nlist = 0;

    if (list == 0)
        return;
    it = list_begin(list);
    nlist = list_create(list->type_meta);
    for (it = list_begin(list); !list_final(list, it); it = it_next(it))
        list_push_front(nlist, list_data(it));
    while (list_len(list) != 0)
        list_pop_front(list);
    for (it = list_begin(nlist); !list_final(nlist, it); it = it_next(it))
        list_push_back(list, list_data(it));
}

void list_iswap(iterator_t *lhs, iterator_t *rhs)
{
    void *data = 0;

    if (lhs == 0 || rhs == 0)
        return;
    data = list_data(*lhs);
    lhs->data = list_data(*rhs);
    rhs->data = data;
}
