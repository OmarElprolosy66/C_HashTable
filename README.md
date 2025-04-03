# Hashtable Project

## Table of Contents
- [Hashmap Project](#hashmap-project)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Requirements](#requirements)
  - [Files](#files)
  - [Building the Project](#building-the-project)
  - [Running the Tests](#running-the-tests)
  - [Usage](#usage)
    - [Hashtable Functions](#hashtable-functions)
    - [Example](#example)
    - [Linking with Static Library](#linking-with-static-library)
    - [Linking with Dynamic Library](#linking-with-dynamic-library)
  - [License](#license)

## Overview
This project implements a simple hashtable in C and includes unit tests to verify its functionality.

## Requirements
- GCC (GNU Compiler Collection) or any compatible C compiler
- Make (build automation tool)

## Files
- `hashtable.c`: Implementation of the hashtable.
- `hashtable.h`: Header file for the hashtable.
- `test_hashtable.c`: Unit tests for the hashtable.
- `Makefile`: Build script for the project.

## Building the Project
To build the project, run the following command:
```sh
make
```
## Running the Tests
```sh
make run_test
```
## Usage
### Hashtable Functions
- hash_table* hash_table_init(size_t size, hashfunc *hf): Creates a new hashtable.
- bool hash_table_insert(hash_table *ht, const char *key, void *obj): Inserts a key-value pair into the hashtable.
- void* hash_table_get(hash_table *ht, const char *key): Retrieves the value associated with a key.
- void* hash_table_delete(hash_table *ht, const char *key): Removes a key-value pair from the hashtable.
- void hash_table_destroy(hash_table *ht, cleanupfunc *cf): Destroys the hashtable and frees memory.

### Example
```c
#include <stdio.h>
#include "hashtable.h"

// Simple hash function
unsigned int simple_hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash;
}

int main() {
    hash_table *ht = hash_table_init(10, simple_hash);

    hash_table_insert(ht, "key1", "value1");
    printf("Inserted key1: %s\n", (char*)hash_table_get(ht, "key1"));

    hash_table_delete(ht, "key1");
    printf("Deleted key1: %s\n", (char*)hash_table_get(ht, "key1"));

    hash_table_destroy(ht, NULL);
    return 0;
}
```
### Linking with Static Library
To link your program with the static library, use the following command:
```sh
gcc -o your_program your_program.c -L. -lhashmap
```

### Linking with Dynamic Library
To link your program with the dynamic library, use the following command:
```sh
gcc -o your_program your_program.c -L. -lhashmap -Wl,-rpath,.
```

## License
This project is licensed under the GPL License. See the LICENSE file for more details.
