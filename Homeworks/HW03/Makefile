CC = gcc
CFLAGS = -Wall -Wextra -g

OBJDIR = obj

PARENT = main
CHILD = forexec/execmain

PARENT_OBJS = \
	$(OBJDIR)/main.o \
	$(OBJDIR)/journey.o

CHILD_OBJS = \
	$(OBJDIR)/execmain.o \
	$(OBJDIR)/getwords.o \
	$(OBJDIR)/out.o


all: $(PARENT) $(CHILD)

$(PARENT): $(PARENT_OBJS)



