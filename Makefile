CC=gcc
MAKE=make
IDIR=algorithms/
CFLAGS=-I$(IDIR) -g -Wall
IDIRFILES=$(IDIR)rc4.o
OBJ=PCE.o $(IDIRFILES)

all:
	$(MAKE) -C $(IDIR)
	$(MAKE) PCE

PCE: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -r *.o 
