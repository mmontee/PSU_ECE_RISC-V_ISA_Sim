parse_input: main.o tests/parse_test.o modules/memory.o modules/risc_sim.o
	gcc -Wall -Wextra -g main.o tests/parse_test.o modules/memory.o modules/risc_sim.o -o app

main.o: main.c modules/risc_sim.h modules/memory.h
	gcc -Wall -Wextra -g -c main.c

tests/parse_test.o: tests/parse_test.c modules/risc_sim.h modules/memory.h
	gcc -Wall -Wextra -g -c tests/parse_test.c -o tests/parse_test.o

modules/memory.o: modules/memory.c modules/memory.h
	gcc -Wall -Wextra -g -c modules/memory.c -o modules/memory.o

modules/risc_sim.o: modules/risc_sim.c modules/risc_sim.h
	gcc -Wall -Wextra -g -c modules/risc_sim.c -o modules/risc_sim.o

parse_test: tests/parse_test.o modules/memory.o modules/risc_sim.o
	gcc -Wall -Wextra -g tests/parse_test.o modules/memory.o modules/risc_sim.o -o parse_test

clean:
	rm -f app parse_test main.o tests/parse_test.o modules/memory.o modules/risc_sim.o
