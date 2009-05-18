CC=gcc
IDIR=./include
ODIR=./obj
SDIR=./src

VPATH=$(SDIR)

TARGET=main

_DEPS = parser.h routing.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o parser.o routing.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CFLAGS=-pedantic -g -Wall -I$(IDIR)

.PHONY: all clean

all: $(TARGET)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) -o $@ $^ 

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ $(SDIR)/*~ $(TARGET)
