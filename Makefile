# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99

# Source directories
SRC_DIR = .
MODULES_DIR = modules
TESTS_DIR = tests

# Headers -- Add headers as needed
HEADERS = $(MODULES_DIR)/risc_sim.h \
          $(MODULES_DIR)/memory.h \
          $(MODULES_DIR)/decode.h \
          $(MODULES_DIR)/execute.h \
          $(MODULES_DIR)/instructions.h

# Module objects -- Add module objects as needed
MODULE_OBJS = $(MODULES_DIR)/memory.o \
              $(MODULES_DIR)/risc_sim.o \
              $(MODULES_DIR)/decode.o \
              $(MODULES_DIR)/execute.o \
              $(MODULES_DIR)/instructions.o

# Executables and their specific objects
MAIN_EXE = main
MAIN_OBJS = $(SRC_DIR)/main.o $(MODULE_OBJS)  # Make sure all needed modules are here

PARSE_TEST_EXE = parse_test
PARSE_TEST_OBJS = $(TESTS_DIR)/parse_test.o $(MODULE_OBJS)

MEM_TEST_EXE = mem_test
MEM_TEST_OBJS = $(TESTS_DIR)/mem_test.o $(MODULE_OBJS)

LX_TEST_EXE = lx_test
LX_TEST_OBJS = $(TESTS_DIR)/lx_test.o $(MODULE_OBJS)

SX_TEST_EXE = sx_test
SX_TEST_OBJS = $(TESTS_DIR)/sx_test.o $(MODULE_OBJS)

TEST_EXES = $(PARSE_TEST_EXE) $(MEM_TEST_EXE) $(LX_TEST_EXE) $(SX_TEST_EXE)

# All objects (for cleaning)
ALL_OBJS = $(MAIN_OBJS) $(PARSE_TEST_OBJS) $(MEM_TEST_OBJS) $(LX_TEST_OBJS) $(SX_TEST_OBJS)

# --- Rules ---

# General rule for compiling .c files (Passes EXTRA_CFLAGS)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

# Executable make cmds
$(PARSE_TEST_EXE): $(PARSE_TEST_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(PARSE_TEST_OBJS) -o $(PARSE_TEST_EXE)

$(MEM_TEST_EXE): $(MEM_TEST_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(MEM_TEST_OBJS) -o $(MEM_TEST_EXE)

$(LX_TEST_EXE): $(LX_TEST_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(LX_TEST_OBJS) -o $(LX_TEST_EXE)

$(SX_TEST_EXE): $(SX_TEST_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(SX_TEST_OBJS) -o $(SX_TEST_EXE)

$(MAIN_EXE): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(MAIN_OBJS) -o $(MAIN_EXE)

# Clean target
clean:
	rm -f $(MAIN_EXE) $(TEST_EXES) $(ALL_OBJS) *.o *.swp

.PHONY: clean all

# Default target
all: $(MAIN_EXE) $(TEST_EXES)
