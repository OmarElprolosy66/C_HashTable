/**
* GNU GENERAL PUBLIC LICENSE
* Version 3, 29 June 2007
* 
* Copyright (C) 2025 OmarElprolosy66
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

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct   _hashtable hash_table;
typedef uint64_t hashfunc(const char*, size_t);
typedef void     cleanupfunc(void*);

hash_table *hash_table_init(size_t size, hashfunc *hf);
bool hash_table_insert(hash_table *ht, const char *key, void *obj);
void *hash_table_get(hash_table *ht, const char *key);
void *hash_table_delete(hash_table *ht, const char *key);
void hash_table_destroy(hash_table *ht, cleanupfunc *cf);

#endif // HASHTABLE_H
