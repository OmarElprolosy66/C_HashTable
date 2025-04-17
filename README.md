# Hashtable Project

## Table of Contents
- [Hashtable Project](#hashtable-project)
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
This will generate:

- A static library: libhashmap.a
- A dynamic library: libhashmap.dll (on Windows) or libhashmap.so (on Linux)
- A test executable: test_hashtable.exe (on Windows) or test_hashtable (on Linux)
## Running the Tests
```sh
make run_test
```
This will compile and run the test_hashtable.c file, which contains unit tests for the hashtable implementation.
## Usage
### Hashtable Functions
- hash_table* hash_table_init(size_t capacity, hashfunc *hf): Creates a new hashtable.
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
    // Initialize the hashtable
    hash_table *ht = hash_table_init(10, simple_hash);

    // Insert key-value pairs
    hash_table_insert(ht, "key1", "value1");
    hash_table_insert(ht, "key2", "value2");

    // Retrieve values
    printf("key1: %s\n", (char *)hash_table_get(ht, "key1"));
    printf("key2: %s\n", (char *)hash_table_get(ht, "key2"));

    // Delete a key-value pair
    hash_table_delete(ht, "key1");
    printf("key1 after deletion: %s\n", (char *)hash_table_get(ht, "key1"));

    // Destroy the hashtable
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
This project is licensed under the GPL License. See the [License](LICENSE) file for more details.
