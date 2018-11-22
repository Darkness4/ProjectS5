# Project Name
TARGET ?= projetS5

# Compiler
CC ?= gcc
CFLAGS ?= -Wall -Wextra -lm -I .

# Linker
LINKER ?= $(CC)
LFLAGS ?= -Wall -I . -lm

# Project structure
SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin
TESTDIR ?= test

# Get all files based on project structure
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Cleaner
rm = rm -f

# Link
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "$(LINKER) $(OBJECTS) $(LFLAGS) -o $@"
	@echo "Linking complete!"


# Compile
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(CC) $(CFLAGS) -c $< -o $@"
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
