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


# Parent executable
$(PARENT): $(PARENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^


# Child executable
$(CHILD): $(CHILD_OBJS)
	$(CC) $(CFLAGS) -o $@ $^


# Parent object files
$(OBJDIR)/main.o: main.c myheader.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/journey.o: journey.c myheader.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Child object files
$(OBJDIR)/execmain.o: forexec/execmain.c myheader.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/getwords.o: getwords.c myheader.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/out.o: out.c myheader.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)


clean:
	rm -rf $(OBJDIR) $(PARENT) $(CHILD)