CC = gcc
CFLAGS := -pie -Wall -Os
TARGET := payload

all:
	$(CC) $(CFLAGS) -o $(TARGET) prepender.c
	
 
clean: $(TARGET)
	rm $(TARGET)

		
