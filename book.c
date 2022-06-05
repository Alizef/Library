#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  
#include <time.h>
#include "book.h"
#include "person.h"


int how_much_book_in_file_text(char * file){ 
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

void show_table(Book *array, int *p_nb_book_in_library){      // Allows us to see all the book present 

    // i represents the index of a book in the array
	for(int i = 0; i < *p_nb_book_in_library; i ++){                        // Display the full array (tab_book)
		printf("\n%d :    %s :    %s :    %s :    %s ", array[i].id, array[i].availability, array[i].title, array[i].author, array[i].category);
	}
    printf("\n");
}

void show_book_borrowed(Person perso_connect, int *p_nb_book_borrowed){       // Allows us to see all the book borrowed and the time of borrow 

    // i represents a borrow (book + time) in the array (book_borrowed)
    for (int i = 0; i< *p_nb_book_borrowed; i++){

        //timeInfos is in seconds since 1970
        struct tm * timeInfos = localtime( & perso_connect.book_borrowed[i].time_max);
        printf("\n%s :    %s :    %s :    %04d/%02d/%02d %02d:%02d:%02d", perso_connect.book_borrowed[i].book.title, perso_connect.book_borrowed[i].book.author, perso_connect.book_borrowed[i].book.category, timeInfos->tm_year+1900, timeInfos->tm_mon+1, timeInfos->tm_mday,
            timeInfos->tm_hour, timeInfos->tm_min, timeInfos->tm_sec);        
            // Displays the current date and manage borrowing time for each book_borrowed with the tm function in time.h
    }
}

int is_book_in_library(Book *array, char name_entered[25], int *p_nb_book_in_library){
    for (int i = 0; i < *p_nb_book_in_library; i++){

        // To compare name_entered and array[i].title and check if they are similar to return the name of the book
        if (strcmp( name_entered, array[i].title) == 0){         
            return i;                                           // i represents the index of the book in the library
        }
    }
    printf("\nThis book does not exist in the library ");
    return -1;
}

// Check if a book is already borrowed with the id
int book_is_in_book_borrowed(Book book, int *p_nb_book_borrowed, Person perso_connect){

    for(int i = 0; i < *p_nb_book_borrowed; i ++){
        if (perso_connect.book_borrowed[i].book.id == book.id){
            return i;
        }
    }
    return -1;
}

int time_max_reached(Person perso_connect, int *p_nb_book_borrowed){

    // Initialize timestamp NULL
    time_t timestamp = time( NULL );
    for (int i= 0; i< *p_nb_book_borrowed; i++){

        // for each book in book_borrowed we check if the maximum time is exceeded
        // if it is we return 0 else 1
        if (perso_connect.book_borrowed[i].time_max < timestamp){
            return 0;
        }
    }
    return 1;
}

void borrowed_book(Book *array, int *p_nb_book_in_library, Person perso_connect, int *p_nb_book_borrowed, int nb_max_book_borrowed){
    
    char name_entered[25]; 
    int verif_scan;
    time_t tempsMax;
    int index;
    
    //Display some messages to explain that perso_connect must have to return the book_borrowed
    if (time_max_reached(perso_connect, p_nb_book_borrowed) == 0){
        printf("\nThe deadline for borrowing one or more of your books has expired   \n");
        printf("Please return it or them before borrowing another one  \n");
    }

    else{
        do{
            printf( "\nEnter the title  --> " );         // check the title 
            verif_scan = scanf( "\n%s", name_entered);

            if (verif_scan != 1){       //verification of the scan
                printf("error1");
                exit(1);
            }
        
        // while the book is not in the library we ask to enter a title 
        index = is_book_in_library(array, name_entered, p_nb_book_in_library);
        }while(index == -1);   
        
        // if the book is already borrowed 
        if (book_is_in_book_borrowed( array[index], p_nb_book_borrowed, perso_connect) != -1){
            printf("\nYou are already borrowing this book\n");
        }
        
        // if all the conditions are OK we can enter in 
        if (book_is_in_book_borrowed(array[index], p_nb_book_borrowed, perso_connect) == -1 && time_max_reached(perso_connect, p_nb_book_borrowed) == 1){ 

            
            time_t timestamp = time(NULL);
            
            if (strcmp( perso_connect.roll, "student" ) == 0){  
                timestamp += 2*60;  // conversion of the 2 minutes into seconds as a student
                }
                
            else{
                timestamp += 3*60;  // conversion of the 3 minutes into seconds as a teacher
            }

            // creation of the book Emprunt in book_borrowed
            perso_connect.book_borrowed[*p_nb_book_borrowed].time_max = timestamp;

            //update in the library of the situation of the book (available or not)
            strcpy( array[index].availability, "    X    ");
            perso_connect.book_borrowed[*p_nb_book_borrowed].book = array[index];
            printf("\n");
            printf( "You have borrowed a book! \n" );
            (*p_nb_book_borrowed)++;
        }
    }
}
 
void return_book(Book *array, int *p_nb_book_in_library, Person perso_connect, int *p_nb_book_borrowed){
    
    char name_entered[25];
    int verif_scan, index_in_library, index_in_borrowed;
    
    do{
        printf( "\nEnter the title  --> " );        //title of the book to be return
        verif_scan = scanf( "\n%s", name_entered);
        if (verif_scan != 1){
            printf("error1");
            exit(1);
        }
    // while the book is not in the library we ask to enter a title 
    index_in_library = is_book_in_library(array, name_entered, p_nb_book_in_library);
    }while(index_in_library == -1);   

    // index in the array book_borrowed (-1 if not in the array)
    index_in_borrowed = book_is_in_book_borrowed(array[index_in_library], p_nb_book_borrowed, perso_connect);

    if (index_in_borrowed != -1){
        // update places in book_borrowed (update the index)
        if ((index_in_borrowed + 1) != *p_nb_book_borrowed){
            for(int j = index_in_borrowed; j < *p_nb_book_borrowed -1; j ++){
                perso_connect.book_borrowed[j] = perso_connect.book_borrowed[j+1];
            }
        }
        (*p_nb_book_borrowed)--;
        // the book is not unavailable anymore
        strcpy(array[index_in_library].availability, "Available");
        printf( "\nYou've returned a book ! \n" );
    }

    else{
        printf( "\n You have not borrowed this book, so you can't return it \n" );   
    }
    
}

void file_transfer_to_table(Book *array, int *p_nb_book_in_library, char * file){
    
    int verif_scan;
	FILE * in = NULL;
    in = fopen(file, "r");
    if (in == NULL){
            printf("error3");
            exit(1);
    }
    // fill in all the books in library.txt to array (tab_book)
	for(int i = 0; i < *p_nb_book_in_library; i ++){
        verif_scan = fscanf(in, "%d :    %s :    %s :    %s :    %s\n", &array[i].id, array[i].availability, array[i].title, array[i].author, array[i].category);
        if (verif_scan != 5){
            printf("error4");
            exit(1);
        }
	}
    fclose(in);
}

int minuscule(char *word){
    int i = 0;
    while (word[i] != '\0'){       // As long as we haven't reached the end of the chain, continue
        if (word[i]  >= 'A' &&  word[i] <= 'Z'){
            word[i] = word[i] + 32;      //Convert upper case letters to lower case 
        }
        if (word[i]  > 'z' ){        //characters in the ASCII code above 122 ('z') are not possible 
            return -1;
        }
        i++;
    }
    return 0;
}

void add_a_book(Book *array, int *p_nb_book_in_library){

    
    char title[25], author[25], id[25];
    int verif_scan;
    int category;
    int index_in_library;

    // convert id to string
    sprintf(id, "%d", *p_nb_book_in_library +1);  

	do{
        printf("\nEnter the title  --> ");      //title of the book to be add
        verif_scan = scanf("%s",title);
        minuscule(title);           //upper letters are convert in lower
        if (verif_scan != 1){
            printf("error5");
            exit(1);
        }
        printf("Enter the author --> ");        
        verif_scan = scanf("%s",author);
        minuscule(author);      //same for the author
        if (verif_scan != 1){
            printf("error6");
            exit(1);
        }
    
    // while the book is in the library we ask to enter a title 
    //while the title and the author are in upper letters 
    index_in_library = is_book_in_library(array, title, p_nb_book_in_library);
    }while(index_in_library != -1 && minuscule(title) == -1 && minuscule(author) == -1);
    printf(", so you can add it \n");


    do{
        // the user has to choose the category with an integer 
        printf( "\n To which category does it belong ? \n " );
        printf( "1-Thriller  2- Literacy  3-Romance  4-Sciences\n" );
        verif_scan = scanf("%d", &category);
        if (verif_scan != 1){
            printf("You did not put an integer");
            exit(1);
        }
    }while (category !=1 && category != 2 && category != 3 && category != 4);
	

    printf("\nCongratulations on adding a book to the library! \n" );

    // We transfer the new book in ibrary.txt
    (*p_nb_book_in_library)++;
    FILE * in = NULL;
    in = fopen("library.txt", "a");
    if (in == NULL){
            printf("error7");
            exit(1);
    }
    fputs("\n", in);
    fputs(id, in);
    fputs(" : ", in);
    fputs("Available", in);
    fputs(" : ", in);
    fputs(title, in);
    fputs(" : ", in);
    fputs(author, in);
    fputs(" : ", in);
    if (category == 1){
        fputs("thriller", in);
    }
    else if(category == 2) {
        fputs("literacy", in);
    }
    else if(category == 3) {
        fputs("romance", in);
    }
    else{
        fputs("sciences", in);
    }
    rewind(in);
    fclose(in);
}

void sort_title(Book *array, int *length_array){
    
    //iterative sort 
    //To sort book according to their title with a sorting by insertion
    Book temp; 
    for (int i = 0; i < *length_array; i++){
        for (int j = 0; j < *length_array; j++){
            if (strcmp(array[i].title, array[j].title) < 0){
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void sort_author(Book *array, int *length_array){
    
    //iterative sort 
    //To sort book according to their title with a sorting by insertion
    Book temp; 
    for (int i = 0; i < *length_array; i++){
        for (int j = 0; j < *length_array; j++){
            if (strcmp(array[i].author, array[j].author) < 0){
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void classement_book(Book *array, int *p_nb_book_in_library){ 
    int choice, verif_scan;
    char choix_category[10];
    do { 

        // You have the choice to choose how you want to sort them 
        printf("\nDo you want to sort ?");
        printf("\n1 - By title \n");
        printf("2 - By authors \n");
        printf("3 - By category \n");

        // Chech the number entered
        verif_scan = scanf("%d", &choice);
        if (verif_scan != 1){
            printf("You did not put a integer");
            exit(1);
        }

        // For each case the table of book will be sorted according to what you have chosen and then this table will be display
        switch (choice){
            case 1 : 
                sort_title(array, p_nb_book_in_library);
                show_table(array, p_nb_book_in_library);
                break;
            case 2 :
                sort_author(array,p_nb_book_in_library);
                show_table(array, p_nb_book_in_library);
                break;
            case 3 :
            do{

                // If you want to see an category in particular, you choose the one you want
                printf("\nWhich category would you like to see?\n");
                printf( "Write thriller - literacy - romance - sciences   --> " );
                verif_scan = scanf("%s", choix_category);
                if (verif_scan != 1){
                    exit(1);
                }
            }while (strcmp("thriller",choix_category) != 0 && strcmp("literacy", choix_category) != 0 && strcmp("romance", choix_category) != 0 && strcmp("sciences", choix_category) != 0);
            
            //display the book of the category choosen 
            for(int i = 0; i < *p_nb_book_in_library; i ++){
                if ( strcmp(array[i].category, choix_category) == 0){
                    printf("\n%d :    %s :    %s :    %s :    %s ", array[i].id, array[i].availability, array[i].title, array[i].author, array[i].category);
                }
            }
            printf("\n");
            break;
            default:
            printf("\n Please enter a number between 1 and 3 \n");
        }
    }while(choice!=1 && choice!=2 && choice !=3);
}