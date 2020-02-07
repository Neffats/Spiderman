CC := gcc
CCFLAGS :=
LDFLAGS :=

spiderman: spiderman.c
	$(CC) $(CCFLAGS) -o spiderman spiderman.c
