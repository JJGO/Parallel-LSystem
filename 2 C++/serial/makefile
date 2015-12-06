 #####################################################################
 # Example MPI C Makefile.
 #####################################################################
 
SRC = serial
CC = g++-5.2.0
CXX = -std=c++11 -O3
 # -fopenmp
ARGS = 20 15
HEADERS = symbol.h lsystem.h fractals.h
OBJECTS = $(SRC).o symbol.o lsystem.o fractals.o

default: $(SRC)

%.o: %.cpp $(HEADERS)
	$(CC) $(CXX) -c $< -o $@

$(SRC): $(OBJECTS)
	$(CC) $(CXX) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(SRC)

run: $(SRC)
	./$(SRC) ${ARGS}
	