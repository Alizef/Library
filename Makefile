all : library

main.o : main.c book.h person.h
	gcc -c $< -o $@

book.o : book.c book.h person.h
	gcc -c $< -o $@

person.o : person.c person.h book.h
	gcc -c $< -o $@

library: person.o book.o main.o
	gcc $^ -o $@