CC=gcc
CFLAGS=-c

testing.exe: main.o queue.o
	$(CC) main.o queue.o -o testing.exe

main.o: main.c
	$(CC) $(CFLAGS) main.c

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

clean:
	rm *.o testing

run:
	./testing.exe

