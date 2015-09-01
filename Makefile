#CC = arm-angstrom-linux-gnueabi-gcc
CC = arm-linux-gnueabihf-gcc
CFLAGS = -O0 -Wall -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=hard -marm
LDFLAGS = -lrt -static



default: bmp.o main.c
	$(CC) $(CFLAGS) $(LDFLAGS) bmp.o main.c -o main -D ORIGIN
	$(CC) $(CFLAGS) $(LDFLAGS) bmp.o main.c -o main_v1 -D VERSION1
	$(CC) $(CFLAGS) $(LDFLAGS) bmp.o main.c -o main_v2 -D VERSION2
	$(CC) $(CFLAGS) $(LDFLAGS) bmp.o main.c -o main_v3 -D VERSION3
	$(CC) $(CFLAGS) $(LDFLAGS) bmp.o main.c -o main_v4

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE) *.o perf.*

