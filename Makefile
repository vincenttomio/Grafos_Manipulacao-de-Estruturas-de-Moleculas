CC     = gcc
CFLAGS = -std=c11
LFLAGS = -Wall

PROG = simulaMol
OBJ = lista.o grafo.o molecula.o $(PROG).o


.PHONY: clean purge all

%.o: %.c lista.h grafo.h molecula.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.o core a.out
	@rm -f $(PROG)
