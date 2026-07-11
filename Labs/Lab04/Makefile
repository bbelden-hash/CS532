CC = gcc

CFLAGS = -Wall -g
DEPS = gettime.h Makefile
OBJS = gettime.o lab04.o 
EXECS = lab04

all: $(EXECS)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

lab04: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	/bin/rm -i *.o $(EXECS)


