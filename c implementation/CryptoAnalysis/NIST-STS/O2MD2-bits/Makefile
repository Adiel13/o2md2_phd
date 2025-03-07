CC=/usr/bin/gcc
LDFLAGS=-lcrypto

SOURCES= kem.c PQCgenKAT_kem.c
HEADERS= api.h params.h params_additionals.h kem.h

PQCgenKAT_kem: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -O3 -g

.PHONY: clean

clean:
	-rm PQCgenKAT_kem PQCkemKAT_64.req PQCkemKAT_64.rsp PQCkemKAT_64_binary.rsp

