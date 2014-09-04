CFLAGS=-O3

INCLUDE=-I.

all: rpn

rpn: scanner.c rpn.c stack.c
	$(CC) scanner.c rpn.c stack.c $(INCLUDE) $(CFLAGS) -o rpn

scanner.c: scanner.ll scanner.h
	flex scanner.ll && mv lex.yy.c scanner.c

clean:
	rm scanner.c rpn