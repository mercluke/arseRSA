CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g 
OBJ=main.o primo.o modexp.o  inversemod.o seed.o

ars: $(OBJ)
	$(CC) -o ars $(OBJ)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c -o main.o main.c

primo.o: primo.c primo.h modexp.h seed.h
	$(CC) $(CFLAGS) -c -o primo.o primo.c

modexp.o: modexp.c modexp.h
	$(CC) $(CFLAGS) -c -o modexp.o modexp.c

inversemod.o: inversemod.c inversemod.h
	$(CC) $(CFLAGS) -c -o inversemod.o inversemod.c

seed.o: seed.c seed.h
	$(CC) $(CFLAGS) -c -o seed.o seed.c
clean:
	rm -rfv $(OBJ) ars keys.txt

