CC=clang++
CFLAGS=-c -std=c++11 -O3

COMMONOBJ=util.o SHA512.o
HASHOBJ=SHA512util.o
HMACOBJ=HMAC.o HMAC-SHA512util.o

all: SHA512util.out HMAC-SHA512util.out

SHA512util.out: $(COMMONOBJ) $(HASHOBJ)
	$(CC) util.o SHA512.o SHA512util.o -o $@

HMAC-SHA512util.out: $(COMMONOBJ) $(HMACOBJ)
	$(CC) util.o SHA512.o HMAC.o HMAC-SHA512util.o -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.out
