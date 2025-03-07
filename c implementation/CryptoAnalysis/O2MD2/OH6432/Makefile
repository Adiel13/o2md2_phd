CC=/usr/bin/gcc
LDFLAGS=-lcrypto -lm

SOURCES= recursive_fft.c common_defs.c kem.c PQCgenKAT_kem.c
HEADERS= common_defs.h api.h params.h params_additionals.h

all: PQCgenKAT_kem PQCgenKAT_kem_debug

# Implementation using traditional multiplication

PQCgenKAT_kem: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -O3

PQCgenKAT_kem_debug: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -DDEBUG_MODE -O3

# Implementation using FFT multiplication

PQCgenKAT_kem_fft: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -DFFT -O3

PQCgenKAT_kem_fft_debug: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LDFLAGS) -DFFT -DDEBUG_MODE -O3

.PHONY: clean

# Clean objects, request and response files

clean:
	-rm PQCgenKAT_kem PQCgenKAT_kem_debug
	-rm PQCkemKAT_32.req PQCkemKAT_32.rsp 
	-rm totalStatistics-O2MD2-OH6432.csv
