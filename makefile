CC = g++
CFLAGS = -O3 -std=c++17 -shared -Wl,
SDIR = ./src

all: int_smallsort float_smallsort

executables:
	mkdir $@

int_smallsort: $(SDIR)/int_smallsort.cpp | executables
	$(CC) $(CFLAGS) -o int_smallsort.so $<
	@mv int_smallsort.so executables/int_smallsort.so

float_smallsort: $(SDIR)/float_smallsort.cpp | executables
	$(CC) $(CFLAGS) -o float_smallsort.so $<
	@mv float_smallsort.so executables/float_smallsort.so

clean:
	rm -rf executables