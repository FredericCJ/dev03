CC=gcc
CFLAGS=-W -Wall -pedantic -std=c17 -Os
LDFLAGS=-g
EXEC=etape1 etape2
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

etape1: etape1.o csv.o
	@$(CC) -o $@ $^ $(LDFLAGS)

etape2: etape2.o csv.o commune.o
	@$(CC) -o $@ $^ $(LDFLAGS)

etape1.o: csv.h config.h
etape2.o: csv.h config.h
csv.o: csv.h config.h
commune.o: csv.h commune.h config.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o *.out

mrproper: clean
	@rm -rf $(EXEC)