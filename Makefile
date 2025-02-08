# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source directories
SRC_DIR = .
MODULES_DIR = modules
TESTS_DIR = tests


#Headers  -- Add headers as needed
HEADERS = 	$(MODULES_DIR)/risc_sim.h \
			$(MODULES_DIR)/memory.h \
			$(MODULES_DIR)/decode.h \
			$(MODULES_DIR)/load_store.h

# Module objects -- Add module objects as needed
MODULE_OBJS = 	$(MODULES_DIR)/memory.o \
				$(MODULES_DIR)/risc_sim.o \
				$(MODULES_DIR)/decode.o \
				$(MODULES_DIR)/load_store.o 
				
				

# Executables and their specific objects
MAIN_EXE = main
MAIN_OBJS = $(SRC_DIR)/main.o $(MODULE_OBJS)  # Make sure all needed modules are here

TEST_EXE = parse_test
TEST_OBJS = $(TESTS_DIR)/parse_test.o $(MODULE_OBJS)

# All objects (for cleaning)
ALL_OBJS = $(MAIN_OBJS) $(TEST_OBJS)

# Rules

	# Programs objs
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/parse_test.o: $(TESTS_DIR)/parse_test.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


	# Modules objs
$(MODULES_DIR)/memory.o: $(MODULES_DIR)/memory.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(MODULES_DIR)/risc_sim.o: $(MODULES_DIR)/risc_sim.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$$(MODULES_DIR)/decode.o: $(MODULES_DIR)/decode.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
$$(MODULES_DIR)/load_store.o: $(MODULES_DIR)/load_store.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


	# Exicutable make cmds
$(TEST_EXE): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_EXE)
	rm -f $(ALL_OBJS) *.o *.swp

$(MAIN_EXE): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) -o $(MAIN_EXE)
	rm -f $(ALL_OBJS) *.o *.swp

clean:
	rm -f $(MAIN_EXE) $(TEST_EXE) $(ALL_OBJS) *.o *.swp

.PHONY: clean

