CC=gcc
CFLAGS=-c -Wall

all: hmac_sha1

clean:
	rm *.o
	rm hmac_sha1_client

hmac_sha1: sha1.o hmac_sha1_client.o hmac.o 
	$(CC) -g sha1.o hmac_sha1_client.o hmac.o  -o hmac_sha1_client

sha1.o: sha1.h sha1.c
	$(CC) $(CFLAGS) sha1.c

hmac.o: hmac.c hmac.h
	$(CC) $(CFLAGS) hmac.c

hmac_sha1_client.o: hmac_sha1_client.c
	$(CC) $(CFLAGS) hmac_sha1_client.c
