PROGRAM_NAME = bin/fifa
TARGET = src/main.cpp
LIBS_FOLDERS = lib
CC = g++
CFLAGS = -g -O3 -Wall -W -pedantic -I $(LIBS_FOLDERS)

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(TARGET)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(TARGET)
	./$(PROGRAM_NAME)
 
clean:
	$(RM) $(PROGRAM_NAME)