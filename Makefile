# Variables
CC = gcc
CFLAGS = -Wall -Werror -fPIC
OPTIM = -O3
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
STATIC_LIB = libhashmap.a
DYNAMIC_LIB = libhashmap.dll
TEST_EXEC = test_hashtable.exe
# Targets
all: static dynamic test

# Create static library from object files
static: $(OBJ)
	ar rcs $(STATIC_LIB) $(OBJ)

# Create dynamic library from object files
dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC_LIB) $(OBJ)

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) $(OPTIM) -c $< -o $@

# Compile and link test binary with static library
test: $(STATIC_LIB) test_hashtable.o
	$(CC) -o $(TEST_EXEC) test_hashtable.o $(STATIC_LIB)

# Run the test
run_test: test
	./$(TEST_EXEC)

# Clean up generated files (Windows compatible version)
clean:
ifeq ($(OS),Windows_NT)
	if exist $(OBJ) del $(OBJ)
	if exist $(STATIC_LIB) del $(STATIC_LIB)
	if exist $(DYNAMIC_LIB) del $(DYNAMIC_LIB)
	if exist $(TEST_EXEC) del $(TEST_EXEC)
	if exist test_hashtable.o del test_hashtable.o
	if exist hashtable.o del hashtable.o
else
	rm -f $(OBJ) $(STATIC_LIB) $(DYNAMIC_LIB) $(TEST_EXEC) test_hashtable.o hashtable.o
endif

.PHONY: all static dynamic test run_test clean
