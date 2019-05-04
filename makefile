CC = gcc

mymat: mat.c mymat.c 
	$(CC) $? -o mymat.exe -g -Wall -ansi -pedantic
	