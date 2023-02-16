CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 

main.out: main.o Library.o book.o document.o mag.o person.o prof.o ref.o student.o
	$(CC) main.o Library.o book.o document.o mag.o person.o prof.o ref.o student.o $(FLAGS) -o main.out

main.o: main.cc Library.hh 
	$(CC) $(COMPILE_FLAGS) main.cc

Library.o: Library.cc Library.hh person.hh document.hh ref.hh book.hh mag.hh student.hh prof.hh
	$(CC) $(COMPILE_FLAGS) Library.cc

person.o: person.cc person.hh document.hh
	$(CC) $(COMPILE_FLAGS) person.cc

document.o: document.cc document.hh 
	$(CC) $(COMPILE_FLAGS) document.cc

student.o: student.cc student.hh person.hh
	$(CC) $(COMPILE_FLAGS) student.cc

prof.o: prof.cc prof.hh person.hh
	$(CC) $(COMPILE_FLAGS) prof.cc

mag.o: mag.cc mag.hh document.hh
	$(CC) $(COMPILE_FLAGS) mag.cc

book.o: book.cc book.hh document.hh
	$(CC) $(COMPILE_FLAGS) book.cc

ref.o: ref.cc ref.hh document.hh
	$(CC) $(COMPILE_FLAGS) ref.cc

.PHONY: clean

clean:
	rm *.o main.out