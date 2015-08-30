CC = arm-angstrom-linux-gnueabi-gcc
CFLAGS = -O0 -Wall
EXECUTABLE = main main_v1 main_v2 main_v3


default: bmp.o main.c
	$(CC) $(CFLAGS) -lrt bmp.o main.c -o main -D ORIGIN
	$(CC) $(CFLAGS) -lrt bmp.o main.c -o main_v1 -D VERSION1
	$(CC) $(CFLAGS) -lrt bmp.o main.c -o main_v2 -D VERSION2
	$(CC) $(CFLAGS) -lrt bmp.o main.c -o main_v3 -D VERSION3

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE) *.o perf.*

