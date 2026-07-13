CC = gcc
CFLAGS = -Wall -Wextra

TARGET = hw02

OBJDIR = obj

OBJS = $(OBJDIR)/main.o \
	   $(OBJDIR)/search.o \
	   $(OBJDIR)/printing.o \
	   $(OBJDIR)/checking.o \
	   $(OBJDIR)/bigTraversal.o

hw02: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) hw02




