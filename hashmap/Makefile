CC= gcc
CFLAGS= -Werror
EXE= out
SOURCES= hashmap.c \
				 testbench.c

$(EXE): clean
	$(CC) $(SOURCES) $(CFLAGS) -o $@

memory: $(EXE)
	leaks --atExit -- ./$(EXE)

clean: 
	rm -f *.o out

