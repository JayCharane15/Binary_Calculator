CC=gcc  #compiler
TARGET=main #target file name
CFLAGS = -Wall -g 

all:    main.o main_suppl_func.o stack.o num.o list.o
	$(CC) $(CFLAGS) main.c main_suppl_func.c stack.c num.c list.c -o $(TARGET) 
 
clean:
	rm *.o $(TARGET)
