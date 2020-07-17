assembler : try.o first_pass.o memory_map.o  definition.h  first_pass.h memory_map.h
	gcc -g -Wall -ansi -pedantic try.o first_pass.o memory_map.o -o assembler

try.o : try.c first_pass.h memory_map.h definition.h
	gcc -c -Wall -ansi -pedantic try.c -o try.o
memory_map.o: memory_map.c memory_map.h definition.h
	gcc -c -Wall -ansi -pedantic memory_map.c -o memory_map.o 
first_pass.o : first_pass.c  first_pass.h  memory_map.c memory_map.h definition.h
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o

