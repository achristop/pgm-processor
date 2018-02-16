# Makefile - A Makefile for the project 3 - Simple Image Process (.pgm)
# Variable definitions
CC = gcc
CFLAGS = -g -c -w
LFLAGS = -o
TARGET = pgm
OBJECTS = main.o interface.o basicOperations.o coreFunctions.o
JUNK_FILES = *.dat *.core
INCLUDES = 
LIBS = 
all: $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
			$(CC) $(LFLAGS) $(TARGET) $(OBJECTS) $(INCLUDES) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $*.c

clean:
		rm -f $(OBJECTS) $(TARGET) $(JUNK_FILES)

run:
		./$(TARGET)