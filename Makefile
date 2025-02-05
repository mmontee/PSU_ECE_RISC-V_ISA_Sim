# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source directories
SRC_DIR = .
MODULES_DIR = modules
TESTS_DIR = tests

# Module objects (generic)
MODULE_OBJS = $(MODULES_DIR)/memory.o $(MODULES_DIR)/risc_sim.o  # Add other module objects as needed

# Executables and their specific objects
MAIN_EXE = main
MAIN_OBJS = $(SRC_DIR)/main.o $(MODULE_OBJS)  # Make sure all needed modules are here

TEST_EXE = parse_test
TEST_OBJS = $(TESTS_DIR)/parse_test.o $(MODULE_OBJS)

# All objects (for cleaning)
ALL_OBJS = $(MAIN_OBJS) $(TEST_OBJS)

# Rules (with explicit dependencies)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(MODULES_DIR)/risc_sim.h $(MODULES_DIR)/memory.h # Add other headers if needed
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/parse_test.o: $(TESTS_DIR)/parse_test.c $(MODULES_DIR)/risc_sim.h $(MODULES_DIR)/memory.h # Add other headers if needed
	$(CC) $(CFLAGS) -c $< -o $@

$(MODULES_DIR)/memory.o: $(MODULES_DIR)/memory.c $(MODULES_DIR)/memory.h
	$(CC) $(CFLAGS) -c $< -o $@

$(MODULES_DIR)/risc_sim.o: $(MODULES_DIR)/risc_sim.c $(MODULES_DIR)/risc_sim.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_EXE): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_EXE)
	rm -f $(ALL_OBJS) *.o *.swp

$(MAIN_EXE): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) -o $(MAIN_EXE)
	rm -f $(ALL_OBJS) *.o *.swp
	
clean:
	rm -f $(MAIN_EXE) $(TEST_EXE) $(ALL_OBJS) *.o *.swp

.PHONY: clean
