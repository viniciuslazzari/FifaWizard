PROGRAM_NAME = bin/fifa
TARGET = src/main.cpp
LIBS_FOLDERS = lib
CC = g++
CFLAGS = -g -Ofast -Wall -W -pedantic -march=native -fopenmp -D_GLIBCXX_PARALLEL -I $(LIBS_FOLDERS)

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(TARGET)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(TARGET)
	./$(PROGRAM_NAME)
 
clean:
	$(RM) $(PROGRAM_NAME)