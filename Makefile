# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -lm

# Target executable
TARGET = graph_program

# Source files
SRCS = main.c graph.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c graph.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
