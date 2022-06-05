#ifndef BOOK_H 
#define BOOK_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//typical structure for a book 
typedef struct Book {
	int id;
	char availability [50];
	char title [50];
	char author [50];
    char category [50];

}Book;

// Structure use for the books borrowed 
typedef struct Borrow{
	Book book;
	time_t time_max;
}Borrow; 

//typical structure for a person
typedef struct Person {
	char login [50];
	char password [50];
    char roll [50];
	Borrow *book_borrowed; 
}Person;



int how_much_book_in_file_text(char * file);	//return the number of books in the file

void show_table(Book *array, int *p_nb_book_in_library);

void show_book_borrowed(Person perso_connect, int *p_nb_book_borrowed);

int is_book_in_library(Book *array, char name_entered[25], int *p_nb_book_in_library);	// if the book is in the library return the index, else -1

int book_is_in_book_borrowed(Book book, int *p_nb_book_borrowed, Person perso_connect);	// if the book is in book_borrowed return the index, else -1

int time_max_reached(Person perso_connect, int *p_nb_book_borrowed);	// return 0 if the time has passed, else 1

void borrowed_book(Book *array, int *p_nb_book_in_library, Person perso_connect, int *p_nb_book_borrowed, int nb_max_book_borrowed);
 
void return_book(Book *array, int *p_nb_book_in_library, Person perso_connect, int *p_nb_book_borrowed);

void file_transfer_to_table(Book *array, int *p_nb_book_in_library, char * file);

int minuscule(char *word);	// return -1 if letters are > 'z', else return 0

void add_a_book(Book *array, int *p_nb_book_in_library);

void sort_title(Book *array, int *length_array);

void sort_author(Book *array, int *length_array);

void classement_book(Book *array, int *p_nb_livre_dans_bibliotheque );


#endif