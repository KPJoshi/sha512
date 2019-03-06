CC=clang++
CFLAGS=-c -std=c++11 -O3

COMMONOBJ=util.o SHA512.o
HASHOBJ=SHA512util.o
HMACOBJ=HMAC.o HMAC-SHA512util.o
PBKDF2OBJ=PBKDF2.o HMAC.o PBKDF2-HMAC-SHA512util.o

all: SHA512util.out HMAC-SHA512util.out PBKDF2-HMAC-SHA512util.out

SHA512util.out: $(COMMONOBJ) $(HASHOBJ)
	$(CC) $(COMMONOBJ) $(HASHOBJ) -o $@

HMAC-SHA512util.out: $(COMMONOBJ) $(HMACOBJ)
	$(CC) $(COMMONOBJ) $(HMACOBJ) -o $@

PBKDF2-HMAC-SHA512util.out: $(COMMONOBJ) $(PBKDF2OBJ)
	$(CC) $(COMMONOBJ) $(PBKDF2OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.out
