CC=gcc
MAKE=make
IDIR=algorithms
CFLAGS=-I$(IDIR) -g -Wall
OBJ=rc4.o PCE.o

all:
	$(MAKE) -C $(IDIR)
	$(MAKE) PCE

PCE: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -r *.o 
