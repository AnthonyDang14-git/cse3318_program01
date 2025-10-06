CC = gcc
CFLAGS = -Wall -g

OBJS = driver.o matching.o 

all: driver

driver: $(OBJS)
	$(CC) $(CFLAGS) -o driver $(OBJS)

clean:
	rm -f *.o driver
