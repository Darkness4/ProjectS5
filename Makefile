# Project Name
TARGET ?= $(shell basename $(CURDIR))

# Compiler
CC ?= gcc
CFLAGS ?= -Wall -Wextra -lm -I .

# Linker
LINKER ?= $(CC)
LFLAGS ?= -Wall -Wextra -lm -I .

# Project structure
SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin

# Cleaner
rm = rm -rf

$(BINDIR)/$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/fonction.o $(OBJDIR)/manip_fichier.o $(OBJDIR)/tableau.o
	@mkdir -p $(BINDIR)
	$(LINKER) $^ $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/fonction.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJDIR)/fonction.o: $(SRCDIR)/fonction.c $(SRCDIR)/fonction.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJDIR)/manip_fichier.o: $(SRCDIR)/manip_fichier.c $(SRCDIR)/manip_fichier.h $(SRCDIR)/fonction.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJDIR)/tableau.o: $(SRCDIR)/tableau.c $(SRCDIR)/tableau.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)
	@echo "Executable removed!"
