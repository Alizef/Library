#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "book.h"
#include "person.h"

int how_much_person(char * file){
	FILE *fileptr;
    int count_lines = 1;
    char letter;
 
    fileptr = fopen(file, "r");
    if (fileptr == NULL){
        printf("erreur14");
        exit(1);
    }
    //extract character from file and store in letter
    letter = getc(fileptr);
    while (letter != EOF)
    {
        //Count whenever new line is encountered
        if (letter == '\n')
        {
            count_lines = count_lines + 1;
        }
        //take next character from file.
        letter = getc(fileptr);
    }
    fclose(fileptr); //close file.
    return count_lines;
    
}

void show_table1(Person *array, int *p_nb_persons){     // Allows us to see all the persons present 

    // i represents the index of a person in the array
	for(int i = 0; i < *p_nb_persons; i ++){         // Display the full array (tab_persons)
		printf("\n%s : %s : %s \n", array[i].login, array[i].password, array[i].roll);
	}
}

int research_student(Person *tab_persons,int *p_nb_persons, char *login_entered, char *password_entered){        

    // search if login_entered and password_entered matches with a login and a password already available 
    // i represents the index of a person in tab_persons
    for (int i = 0; i < *p_nb_persons; i++) {
        if (strcmp( login_entered, tab_persons[i].login ) == 0 && strcmp( password_entered,tab_persons[i].password ) == 0){
            return i;
        }
    }
    printf( "\nPlease try again\n" );
    return -1;
}

int research_login(Person *tab_persons,int *p_nb_persons, char *login_entered){    

    //same as research_student but just for the login    
    for (int i = 0; i < *p_nb_persons; i++) {

        // Checks if the login_entered and tab_student[i].login are similar
        if (strcmp( login_entered, tab_persons[i].login ) == 0){
            printf( "\n This account already exists, please change your login \n" );
            return 0;
        }
    }
    return -1;
}

int connection_account(Person *tab_persons, int *p_nb_persons){

    char login_entered[25], password_entered[25];
    int verif_scan, i;

    do{
        printf( "\nPlease, enter your login:  " );
        verif_scan = scanf( "%s", login_entered );      

        if (verif_scan != 1){       // check if the scanf happened well
            printf("erreur8");
            exit(1);
        }

        printf( "\nEnter your password:  " );
        verif_scan = scanf( "%s", password_entered );
        if (verif_scan != 1){
            printf("erreur9");
            exit(1);
        }
        // i represents the index of the person in tab_persons
        // if i == -1 it means that the person does not exist in persons.txt
        i = research_student(tab_persons, p_nb_persons, login_entered, password_entered);
    }while (i == -1);
    printf(   "\n         -----------------------------------              \n" );
    printf(   "\n               Welcome to the library                \n" );
    printf(   "                       %s                           \n", login_entered );
    return i;
}

void file_transfer_to_table1(Person *array, int *p_nb_persons, char * file){

    int verif_scan;
	FILE * in = NULL;
    in = fopen(file, "r");      // opening the file persons.txt
    if (in == NULL){
            printf("erreur10");
            exit(1);
    }

    // i represents each person in the file
	for(int i = 0; i < *p_nb_persons; i ++){
        verif_scan = fscanf(in,"%s : %s : %s \n", array[i].login, array[i].password, array[i].roll);
        if (verif_scan != 3){
            printf("erreur11");
            exit(1);
        }
        
	}
    fclose(in);
}

void create_account(Person *tab_persons,int *p_nb_persons){

    // Function necessary to create an account and check in the file person.txt if this person exist

    int student_or_teacher; // whatever its role a student or a teacher
    char login_entered[25], password_entered[25]; // Create two variables, one for the login and one for the password 
    int verif_scan;

    do{
        printf( "\nPlease, enter your login :  " );
        verif_scan = scanf( "%s", login_entered );
        if (verif_scan != 1){
            printf("Erreur lors de la saisie\n");
            exit(1);
        }

        printf( "\nEnter your password:  " );
        verif_scan = scanf( "%s", password_entered );
        if (verif_scan != 1){
            printf("Erreur lors de la saisie\n");
            exit(1);
        }

        // while the login already exists
    }while (research_login(tab_persons, p_nb_persons, login_entered) == 0);
    do{
        printf( "\n Are you 1 - student or 2 - teacher?  " );
        verif_scan = scanf( "%d", &student_or_teacher);
        if (verif_scan != 1){
            printf(" You did not put an integer ");
            exit(1);
        }

         // while you didn't put 1 or 2
    }while (student_or_teacher !=1 && student_or_teacher != 2);

    //the creation is succesful so this new infomations will be add at person.txt   
    printf(   "\n Congratulations on creating your account! \n" );

    FILE * in = NULL;
    in = fopen("person.txt", "a");
    if (in == NULL){
        printf("erreur14");
        exit(1);
    }
    fputs("\n", in);
    fputs(login_entered, in);
    fputs(" : ", in);
    fputs(password_entered, in);
    fputs(" : ", in);
    if (student_or_teacher == 1){
        fputs("student", in);
    }
    else{
        fputs("teacher", in);
    }
    rewind(in);
    fclose(in);
    
}
