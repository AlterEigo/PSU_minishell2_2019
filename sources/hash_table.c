/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include "hash_table.h"

const meta_bundle_t MB_HT_ITEM = {
    ht_item_copy,
    ht_item_destroy,
    sizeof(ht_item_t)
};

hash_value_t hash_str(char const *str)
{
    hash_value_t hash = 47441;
    char c;

    while (*str) {
        c = *str;
        hash = ((hash << 5) + hash) + c;
        str++;
    }
    return (hash);
}

map_t *map_create(unsigned int size, meta_bundle_t meta)
{
    map_t *map = malloc(sizeof(map_t));

    map->type_meta = meta;
    map->array_size = size;
    map->data_table = malloc(sizeof(list_t*) * size);
    for (uint_t i = 0; i < size; i++)
        map->data_table[i] = list_create(MB_HT_ITEM);
    return (map);
}

void map_insert(map_t *map, hash_value_t key, void const *value)
{
    ht_item_t *nitem = 0;
    list_t *list = 0;
    void *copy = 0;

    if (map == 0)
        return;
    if (map->type_meta.copy == 0)
        copy = mem_copy(value, map->type_meta.data_size);
    else
        copy = map->type_meta.copy(value);
    nitem = ht_item_create(key, copy);
    key = key % map->array_size;
    list = map->data_table[key];
    list_push_front(list, nitem);
    ht_item_free(&nitem);
}

void *map_get(map_t *map, hash_value_t key)
{
    list_t *list = 0;
    iterator_t it;
    ht_item_t *item = 0;

    if (map == 0)
        return (0);
    list = map->data_table[key % map->array_size];
    it = list_begin(list);
    for (uint_t i = 0; i < list_len(list); i++, it = it_next(it)) {
        item = (ht_item_t*)list_data(it);
        if (item->key == key)
            return (item->value);
    }
    return (0);
}

void *map_pull(map_t *map, hash_value_t key)
{
    list_t *list = 0;
    iterator_t it;
    ht_item_t *item = 0;
    void *data = 0;

    if (map == 0)
        return (0);
    list = map->data_table[key % map->array_size];
    it = list_begin(list);
    for (uint_t i = 0; i < list_len(list); i++, it = it_next(it)) {
        item = (ht_item_t*)list_data(it);
        if (item->key == key) {
            item = list_pull(list, it);
            data = item->value;
            ht_item_free(&item);
            return (data);
        }
    }
    return (0);
}

uint_t map_count(map_t const *map)
{
    uint_t len = 0;
    list_t *current = 0;

    for (uint_t i = 0; i < map->array_size; i++) {
        current = map->data_table[i];
        len += list_len(current);
    }
    return (len);
}

static void free_item_content(ht_item_t *item, destructor_ft destroy)
{
    if (item == 0)
        return;
    if (destroy == 0)
        free(item->value);
    else
        destroy(item->value);
}

void map_free(map_t **pmap)
{
    ht_item_t *item;
    iterator_t it;
    uint_t llen;

    if (pmap == 0 || *pmap == 0)
        return;
    for (uint_t i = 0; i < (*pmap)->array_size; i++) {
        it = list_begin((*pmap)->data_table[i]);
        llen = list_len((*pmap)->data_table[i]);
        for (uint_t j = 0; j < llen; j++, it = it_next(it)) {
            item = (ht_item_t*)list_data(it);
            free_item_content(item, (*pmap)->type_meta.destroy);
        }
        list_free(&(*pmap)->data_table[i]);
    }
    free((*pmap)->data_table);
    free(*pmap);
    (*pmap) = 0;
}

ht_item_t *ht_item_create(hash_value_t key, void *value)
{
    ht_item_t *item = malloc(sizeof(ht_item_t));

    item->key = key;
    item->value = value;
    return (item);
}

void ht_item_free(ht_item_t **item)
{
    if (item == 0 || (*item) == 0)
        return;
    free(*item);
    (*item) = 0;
}

void *ht_item_copy(void const* item)
{
    ht_item_t *old = (ht_item_t*)item;
    ht_item_t *nitem = 0;

    if (old == 0)
        return (0);
    nitem = ht_item_create(old->key, old->value);
    return (nitem);
}

void ht_item_destroy(void *item)
{
    ht_item_t *tmp = (ht_item_t*)item;

    ht_item_free(&tmp);
}
