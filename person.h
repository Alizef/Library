#ifndef PERSON_H
#define PERSON_H
#include "book.h"

int how_much_person(char * file);   // return the number of persons in persons.txt

void show_table1(Person *array, int *p_nb_persons);

int research_student(Person *tab_persons,int *p_nb_persons, char *login_entered, char *password_entered); // if the person is in the file return the index, else -1

int research_login(Person *tab_persons,int *p_nb_persons, char *login_entered);     // if only the login is in the file return the index, else -1

int connection_account(Person *tab_persons, int *p_nb_persons);     //  return the index of the person in tab_persons

void file_transfer_to_table1(Person *array, int *p_nb_persons, char * file);

void create_account(Person *tab_persons,int *p_nb_persons);

#endif