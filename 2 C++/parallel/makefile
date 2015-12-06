 #####################################################################
 # Example MPI C Makefile.
 #####################################################################
 
CC = g++-5.2.0
CFLAGS =
# -O3
# -std=c++11
HEADERS = symbol.h lsystem.h fractals.h
OBJECTS = symbol.o lsystem.o fractals.o
TARGETS = naive lookahead

all: $(TARGETS)

naive:  naive.o $(OBJECTS)
	$(CC) -fopenmp $(CFLAGS) $^ -o $@

lookahead:  lookahead.o $(OBJECTS)
	$(CC) -fopenmp $(CFLAGS) $^ -o $@

.cpp.o:
	$(CC) -fopenmp $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGETS)
	-rm -f *.txt

test:
	./test.sh naive 10 100 10
	./test.sh lookahead 10 100 10

	