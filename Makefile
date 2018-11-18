# Project Name
TARGET = projetS5

# Compiler
CC ?= gcc
CFLAGS ?= -c -Wall -Wextra -I .

# Linker
LINKER ?= $(CC)
LFLAGS ?= -Wall -I . -lm

# Project structure
SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin

# Get all files based on project structure
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Cleaner
rm = rm -f

# Link
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

# Compile
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
