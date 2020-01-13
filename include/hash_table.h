/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#include "common_types.h"
#include "iterator.h"
#include "list.h"

typedef struct HashTableItem {
    hash_value_t key;
    void *value;
} ht_item_t;

ht_item_t *ht_item_create(hash_value_t key, void *value);
void ht_item_free(ht_item_t **item);
void *ht_item_copy(void const* item);
void ht_item_destroy(void *item);

extern const meta_bundle_t MB_HT_ITEM;

typedef struct HashTable
{
    unsigned int array_size;
    list_t **data_table;
    meta_bundle_t type_meta;
} map_t;

map_t *map_create(unsigned int size, meta_bundle_t meta);

hash_value_t hash_str(char const *str);
void map_resize(map_t *map, unsigned int size);
uint_t map_count(map_t const *map);

void map_insert(map_t *map, hash_value_t, void const *value);
void *map_get(map_t *map, hash_value_t);
void *map_pull(map_t *map, hash_value_t);
void const *map_cget(map_t const map, hash_value_t);

void map_free(map_t **map);

#endif
