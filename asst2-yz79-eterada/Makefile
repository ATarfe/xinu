CFLAGS=-O2 -lm

INCLUDE=-Incurses/include

LDFLAGS=-Lncurses/lib -lncurses -ldl

OBJS=main.o

all: main

main: ${OBJS}
	$(CC) ${OBJS} $(INCLUDE) $(CFLAGS) $(LDFLAGS) -o main

clean:
	rm -f *.o

distclean:
	rm -f main *.o 

#inference for all .c files not listed above...
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -c -o $@ $^
	
