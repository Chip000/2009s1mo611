CC=gcc
IDIR=./include
ODIR=./obj
SDIR=./src

VPATH=$(SDIR)

TARGET=main

_DEPS = parser.h shortest_path.h struct_route.h routing.h graph_aux.h neighbor.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o parser.o shortest_path.o struct_route.o routing.o graph_aux.o neighbor.o
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
