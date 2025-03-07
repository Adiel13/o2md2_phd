CC=/usr/bin/gcc

SOURCES = params.c statisticsFileNames.c Main.c
HEADERS = params.h statisticsFileNames.h

statisticsMerger: $(HEADERS) $(SOURCES)
	$(CC) -o $@ $(SOURCES) -g

.PHONY: clean

clean:
	-rm statisticsMerger StatisticsTotal.csv

rebuild: clean
	make
