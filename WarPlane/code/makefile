PROGRAM = game
CC = gcc
CFLAGS = -Wall -Wno-unused-variable
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM) : main.o callback.o init.o objects.o draw.o timer.o allocation.o image.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

allocation.o : allocation.c allocation.h
	$(CC) $(CFLAGS) -c -o $@ $<

timer.o : timer.c timer.h
	$(CC) $(CFLAGS) -c -o $@ $<

draw.o : draw.c draw.h
	$(CC) $(CFLAGS) -c -o $@ $<

objects.o : objects.c objects.h
	$(CC) $(CFLAGS) -c -o $@ $<

init.o : init.c init.h
	$(CC) $(CFLAGS) -c -o $@ $<

callback.o : callback.c callback.h	
	$(CC) $(CFLAGS) -c -o $@ $<

image.o : image.c image.h 
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c
	$(CC) $(CFLAGS) -c -o $@ $< 




PHONY : clean

clean:
	rm -rf *.o $(PROGRAM)
