#include <stdio.h>
#include <string.h>
#include "hashtable.h"

uint64_t simple_hash(const char *key, size_t len) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash;
}

void test_insert() {
    hash_table *ht = hash_table_init(1, simple_hash);
    if (hash_table_insert(ht, "key1", "value1")) {
        printf("Insert test passed\n");
    } else {
        printf("Insert test failed\n");
    }

    if (strcmp(hash_table_get(ht, "key1"), "value1") == 0) {
        printf("Get test passed\n");
    } else {
        printf("Get test failed\n");
    }
    hash_table_destroy(ht, NULL);
}

void test_remove() {
    hash_table *ht = hash_table_init(1, simple_hash);
    hash_table_insert(ht, "key2", "value2");
    if (hash_table_delete(ht, "key2")) {
        printf("Remove test passed\n");
    } else {
        printf("Remove test failed\n");
    }

    if (hash_table_get(ht, "key2") == NULL) {
        printf("Get after remove test passed\n");
    } else {
        printf("Get after remove test failed\n");
    }
    hash_table_destroy(ht, NULL);
}

int main() {
    printf("Running tests...\n");
    test_insert();
    test_remove();
    printf("Tests completed.\n");
    return 0;
}