 #####################################################################
 # Example MPI C Makefile.
 #####################################################################
 
SRC = test
CC = g++-5.2.0

HEADERS = symbol.h lsystem.h fractals.h
OBJECTS = $(SRC).o symbol.o lsystem.o fractals.o

default: $(SRC)

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

$(SRC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(SRC)

run: $(SRC)
	./${SRC}
	