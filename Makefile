CC = gcc
CFLAGS := -pie -Wall -Os
TARGET := prepender

all:
	$(CC) $(CFLAGS) -o $(TARGET) prepender.c
	
clean:
	rm $(TARGET)
