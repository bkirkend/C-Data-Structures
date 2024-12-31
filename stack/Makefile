CC= gcc
CFLAGS= -Werror
EXE= out
SOURCES= src/stack.c \
				 int/stack_int.c \
				 main.c

$(EXE): clean
	$(CC) $(SOURCES) $(CFLAGS) -o $@

memory: $(EXE)
	leaks --atExit -- ./$(EXE)

clean: 
	rm -f *.o out

