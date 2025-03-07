CC=/usr/bin/gcc
LDFLAGS=-lcrypto

SOURCES= cbd.c fips202.c indcpa.c kem.c ntt.c poly.c polyvec.c PQCgenKAT_kem.c reduce.c rng.c verify.c symmetric-fips202.c
HEADERS= api.h cbd.h fips202.h indcpa.h ntt.h params.h poly.h polyvec.h reduce.h rng.h verify.h symmetric.h

PQCgenKAT_kem: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -g

.PHONY: clean

clean:
	-rm PQCgenKAT_kem PQCkemKAT_1632.req PQCkemKAT_1632.rsp totalStatisticsCRYSTAL0512-Nano.csv

