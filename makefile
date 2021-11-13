CC=clang
CFLAGS=-W -Wall -pedantic -std=c17 -g
LDFLAGS=-g
EXEC=etape1 etape2 etape3
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

etape1: etape1.o csv.o
	@$(CC) -o $@ $^ $(LDFLAGS)

etape2: etape2.o csv.o commune.o
	@$(CC) -o $@ $^ $(LDFLAGS)

etape3: etape3.o csv.o commune.o
	@$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o *.out

mrproper: clean
	@rm -rf $(EXEC)
