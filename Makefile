# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99

# Source directories
SRC_DIR = .
MODULES_DIR = modules
TESTS_DIR = tests

#Headers  -- Add headers as needed
HEADERS =   $(MODULES_DIR)/risc_sim.h \
        $(MODULES_DIR)/memory.h \
        $(MODULES_DIR)/decode.h \
        $(MODULES_DIR)/execute.h  \
        $(MODULES_DIR)/instructions.h

# Module objects -- Add module objects as needed
MODULE_OBJS =   $(MODULES_DIR)/memory.o \
        $(MODULES_DIR)/risc_sim.o \
        $(MODULES_DIR)/decode.o \
        $(MODULES_DIR)/execute.o \
        $(MODULES_DIR)/instructions.o

# Executables and their specific objects
MAIN_EXE = main
MAIN_OBJS = $(SRC_DIR)/main.o $(MODULE_OBJS)  # Make sure all needed modules are here

TEST_EXE = parse_test
TEST_OBJS = $(TESTS_DIR)/parse_test.o $(MODULE_OBJS)

# All objects (for cleaning)
ALL_OBJS = $(MAIN_OBJS) $(TEST_OBJS)

# --- Rules ---

# General rule for compiling .c files (Passes EXTRA_CFLAGS)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

# Executable make cmds
$(TEST_EXE): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(TEST_OBJS) -o $(TEST_EXE)

$(MAIN_EXE): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(MAIN_OBJS) -o $(MAIN_EXE)

# Clean target
clean:
	rm -f $(MAIN_EXE) $(TEST_EXE) $(ALL_OBJS) *.o *.swp

.PHONY: clean all

#Default target
all: $(MAIN_EXE)

