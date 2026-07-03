
CC = gcc
CFLAGS = -I
DEPS = someFunc.h
OBJ = lectureThreeExercises.o someFunc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) /workspaces/CS532/stuffShellRandom

myExecutable: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) /workspaces/CS532/stuffShellRandom


