CC=gcc
CFLAGS=-Wall -Wextra -Werror=implicit-function-declaration -Werror=format-security -pedantic -std=c17 -g -O2

SRCDIR=src
BUILDDIR=build
TARGETDIR=bin

SOURCES=$(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXE=$(TARGETDIR)/lsm

all: $(EXE)

$(EXE): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find $(BUILDDIR) -type f -name '*.o' -exec rm -f {} +
	find $(TARGETDIR) -type f ! -name '.gitkeep' -exec rm -f {} +