/*
* GNU GENERAL PUBLIC LICENSE
* Version 3, 29 June 2007
* 
* Copyright (C) 2024 OmarElprolosy66
* 
* Everyone is permitted to copy and distribute verbatim copies
* of this license document, but changing it is not allowed.
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"

typedef struct _kvpair {
    const char     *key;
    void           *obj;
    struct _kvpair *next;
} kvpair;

typedef struct _hashtable {
    size_t      size;
    hashfunc    *hf;
    kvpair      **kvpairs;
} hash_table;

hash_table *hash_table_init(size_t size, hashfunc *hf)
{
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    if (ht == NULL) return NULL;

    *ht = (hash_table) {
        .size    = size,
        .hf      = hf,
        .kvpairs = (kvpair **)calloc(sizeof(kvpair *), size)
    };
    if (ht->kvpairs == NULL) return NULL;

    return ht;
}

bool hash_table_insert(hash_table *ht, const char *key, void *obj)
{
    if ((ht == NULL) || (key == NULL) || (obj == NULL)) return false;

    if (hash_table_get(ht, key) != NULL) return false;

    uint32_t index = ht->hf(key, strlen(key)) % ht->size;

    kvpair *kvp = (kvpair *)malloc(sizeof(kvpair));
    if (kvp == NULL) return false;

    *kvp = (kvpair) {
        .key = strdup(key),
        .obj = obj
    };
    if (kvp->key == NULL) {
        free(kvp);
        return false;  // strdup failed
    }

    kvp->next = ht->kvpairs[index];
    ht->kvpairs[index] = kvp;

    return true;
}

/**
 * @brief deallocates the hash table
 * @param ht the hash table pointer
 * @param cf function pointer to a custom cleanup function for deallocating dynamically allocated objects defined by user.
 *  it should be NULL if the objects is statically allocated or the user want to handel the deallocation by himself.
 */
void hash_table_destroy(hash_table *ht, cleanupfunc *cf)
{ 
    for (uint32_t i = 0; i < ht->size; i++) {
        while (ht->kvpairs[i] != NULL) {
            kvpair *tmp    = ht->kvpairs[i];
            ht->kvpairs[i] = ht->kvpairs[i]->next;

            free((void *)tmp->key);
            tmp->key = NULL;

            if (cf != NULL) cf(tmp->obj);

            free(tmp); tmp = NULL;
        }
    }

    free(ht->kvpairs); ht->kvpairs = NULL;
    free(ht); ht = NULL;
}

void *hash_table_delete(hash_table *ht, const char *key)
{
    if ((ht == NULL) || (key == NULL)) return NULL;

    uint32_t index = ht->hf(key, strlen(key)) % ht->size;

    kvpair *tmp  = ht->kvpairs[index];
    kvpair *prev = NULL;
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp  = tmp->next;
    }

    if (tmp  == NULL) return NULL; // not found!
    if (prev == NULL) ht->kvpairs[index] = tmp->next; // prev hasn't been assigned yet to the tmp.
    else prev->next = tmp->next;

    void *result = tmp->obj;
    free(tmp); tmp = NULL;

    return result; // user desides how to free the obj.
}

void *hash_table_get(hash_table *ht, const char *key)
{
    if ((ht == NULL) || (key == NULL)) return NULL;

    uint32_t index = ht->hf(key, strlen(key)) % ht->size;

    kvpair *tmp = ht->kvpairs[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }

    if (tmp == NULL) return NULL; // not found!

    return tmp->obj;
}
