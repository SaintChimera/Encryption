CC=gcc
MAKE=make
TARGET=PCE
IDIR=algorithms/
CFLAGS=-I$(IDIR) -g -Wall
IDIRFILES=$(IDIR)rc4.o
OBJ=PCE.o $(IDIRFILES)

all:
	$(MAKE) -C $(IDIR)
	$(MAKE) PCE

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -r *.o 
	rm -r $(TARGET)
	$(MAKE) clean -C $(IDIR)
