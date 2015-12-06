 #####################################################################
 # Example MPI C Makefile.
 #####################################################################
 
CC = g++-5.2.0
CFLAGS = -O3
# -std=c++11
HEADERS = symbol.h lsystem.h fractals.h
OBJECTS = symbol.o lsystem.o fractals.o
TARGETS = parallel_naive parallel_queues

all: $(TARGETS)

parallel_naive:  parallel_naive.o $(OBJECTS)
	$(CC) -fopenmp $(CFLAGS) $^ -o $@

parallel_queues:  parallel_queues.o $(OBJECTS)
	$(CC) -fopenmp $(CFLAGS) $^ -o $@

.cpp.o:
	$(CC) -fopenmp $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGETS)

test:
	./test.sh parallel_naive 10 100 10

	