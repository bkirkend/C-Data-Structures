CC=gcc
CFLAGS= -Werror
EXE= out
DEPS= stack.h
OBJ= main.o stack.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

memory: $(EXE)
	leaks --atExit -- ./$(EXE)

clean: 
	rm -f *.o out

