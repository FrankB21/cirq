CC=gcc
CWARNS=-Wall -Wextra -Wshadow -Wcast-align \
-Wpedantic -Wunused -Wconversion -Wsign-conversion \
-Wmisleading-indentation -Wnull-dereference \
-Wdouble-promotion -Wformat=2

INCDIR=include

CFLAGS=$(CWARNS) -std=gnu17 -I$(INCDIR)

SRCDIR=src
OBJDIR=obj

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

TESTDIR=tests
TESTSRCS=$(wildcard $(TESTDIR)/*.c)
TESTBINS=$(patsubst $(TESTDIR)/%.c, $(TESTDIR)/bin/%, $(TESTSRCS))

LIBDIR=lib
LIB=$(LIBDIR)/libcirq.a

all: CFLAGS+=-g
all: $(LIB)

release: CFLAGS+=-O3 -DNDEBUG
release: clean
release: $(LIB)

test: CFLAGS+=-g
test: $(LIB) $(TESTDIR)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

$(LIB): $(LIBDIR) $(OBJDIR) $(OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTDIR)/bin/%: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

$(TESTDIR)/bin:
	mkdir $@

$(OBJDIR):
	mkdir $@

$(LIBDIR):
	mkdir $@

.PHONY: clean
clean:
	$(RM) -r $(LIBDIR) $(OBJDIR) $(TESTDIR)/bin
