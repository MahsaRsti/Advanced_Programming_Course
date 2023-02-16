CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 

utaxi.out: main.o driver.o error.o input.o passenger.o person.o trips.o locations.hpp
	$(CC) main.o driver.o error.o input.o passenger.o person.o trips.o $(FLAGS) -o utaxi.out

main.o: main.cpp input.hpp person.hpp driver.hpp passenger.hpp error.hpp trips.hpp
	$(CC) $(COMPILE_FLAGS) main.cpp

input.o: input.cpp input.hpp person.hpp driver.hpp passenger.hpp error.hpp trips.hpp locations.hpp
	$(CC) $(COMPILE_FLAGS) input.cpp

person.o: person.cpp person.hpp
	$(CC) $(COMPILE_FLAGS) person.cpp

driver.o: driver.cpp driver.hpp person.hpp
	$(CC) $(COMPILE_FLAGS) driver.cpp

passenger.o: passenger.cpp passenger.hpp person.hpp
	$(CC) $(COMPILE_FLAGS) passenger.cpp

trips.o: trips.cpp trips.hpp input.hpp
	$(CC) $(COMPILE_FLAGS) trips.cpp

error.o: error.cpp error.hpp input.hpp
	$(CC) $(COMPILE_FLAGS) error.cpp

locations.o: locations.hpp
	
.PHONY: clean

clean:
	rm *.o utaxi.out