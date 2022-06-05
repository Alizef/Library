#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "person.h"
#include "book.h"


// rajouter des free (tab)



void line(){
    printf("\n ****************************************************** \n");
}

int connection(){
    int verif_scan; 
    int choice;
    do{
        // Logging in to your account or creating an account         
        printf("\n1 - Login \n");                               // Logging in to your account or creating an account  
        printf("\n2 - New user \n");
        printf("\n3 - Exit\n");
        verif_scan =  scanf("%d", &choice);

        if (verif_scan != 1){                           
            printf("You did not put an integer");    // Test; Allows you to check the scanf and if it is a integer
            exit(1);
        }

    }while(choice>3 || choice<1);
    return choice;
}


 // Only concerns students
void student_session(Person perso_connect, Book * tab_book, int *p_nb_book_in_library){ 

    int nb_book_borrowed = 0;
    int nb_max_book_borrowed = 3;                           // Students can borrowed until 3 books
    int *p_nb_book_borrowed = &nb_book_borrowed;
    int choice;
    int verif_scan;

    do { 
        // Students can choose what they want to do
        printf("\nWhat do you want to do?  \n");   
        printf("\n 1 - See the books available in the library \n");
        printf("\n 2 - Borrow a new book \n");
        printf("\n 3 - Return a book \n");
        printf("\n 4 - View borrowed books  \n");
        printf("\n 5 - Disconnect \n");
        verif_scan = scanf("%d", &choice);

        if (verif_scan != 1){
            printf("You did not put an integer");
            exit(1);
        }

        switch (choice){

            case 1 : 
            // sort the book by author, title or category

            classement_book(tab_book, p_nb_book_in_library);
            break;

            case 2 :
            // Allows you to check whether the number of books already borrowed is less than the maximum possible number to borrow

            if (*p_nb_book_borrowed < nb_max_book_borrowed){

                // if the person already borrowed books they will be display
                if (*p_nb_book_borrowed > 0){
                    printf("\n You have borrowed %d book(s) \n", *p_nb_book_borrowed);
                    show_book_borrowed(perso_connect, p_nb_book_borrowed);
                    printf("\n");
                }
                // sort the book by author, title or category
                classement_book(tab_book, p_nb_book_in_library);
                // function to borrow a book
                borrowed_book(tab_book, p_nb_book_in_library, perso_connect, p_nb_book_borrowed, nb_max_book_borrowed); 
            }
            else{
                // students can only borrow 3 books that the reason why they have to return one in order to borrow an other book
                printf("\n You already own 3 books \n");
                printf("\n Please return one before borrowing another :) \n");
            }
            break;

            case 3 :
            // if the person already borrowed books they will be display
            if (*p_nb_book_borrowed>0){
                printf("\n You have borrowed %d book(s) \n", *p_nb_book_borrowed);
                printf("\n You have already borrowed the following book(s) : \n");
                show_book_borrowed(perso_connect, p_nb_book_borrowed);
                printf("\n");
                // function to return a book
                //Allows you to return a borrowed book after checking its presence in your personal borrowing list
                return_book(tab_book, p_nb_book_in_library, perso_connect, p_nb_book_borrowed);
            }
            else{
                printf("\nYou have not borrowed any books\n");
                printf(" Please borrow one before returning another :) \n");
            }
            break;

            case 4 :
            // if the person already borrowed books they will be display
            if (*p_nb_book_borrowed > 0){
                show_book_borrowed(perso_connect, p_nb_book_borrowed);
                printf("\n");
            }
            else{
                printf("\n You have not borrowed any books \n");
            }
            break;

            case 5 :
                printf("\n Goodbye ! \n");
                break;

            default : 
            // Secure case
                printf("\n Please enter a number between 1 and 5 \n");
                break;
        }
    }while(choice!=5);
}


 // Only concerns teacher
void teacher_session(Person perso_connect, Book * tab_book, int *p_nb_book_in_library){
    int nb_book_borrowed = 0;
    int nb_max_book_borrowed = 5;        // Students can borrowed until 5 books
    int *p_nb_book_borrowed = &nb_book_borrowed;
    int choice;
    int verif_scan;

    do { 
        // Teachers can choose what they want to do
        printf("\nWhat do you want to do? \n");
        printf("\n 1 - See the books available in the library \n");
        printf(" 2 - Borrow a new book \n");
        printf(" 3 - Return a book \n");
        printf(" 4 - View borrowed books  \n");

         // They can add some book to the library which is not possible for a student
        printf(" 5 - Add a book in the library \n");               
        printf(" 6 - Disconnect\n");
        verif_scan = scanf("%d", &choice);

         // Check if the number enter exist or not
        if (verif_scan != 1){
            printf("You did not put a integer");
            exit(1);
        }

        switch (choice){

            case 1 : 
            // sort the book by author, title or category
            classement_book(tab_book, p_nb_book_in_library);
            break;

            case 2 :
             // check if your numer of book borrowed is less than 5 and if it's the case you can see the book borrowed and borrowed a new one
            if (*p_nb_book_borrowed < nb_max_book_borrowed){

                if (*p_nb_book_borrowed > 0){
                    printf("\n You have borrowed %d book(s) \n", *p_nb_book_borrowed);
                    show_book_borrowed(perso_connect, p_nb_book_borrowed);
                    printf("\n");
                }
                classement_book(tab_book, p_nb_book_in_library);
                borrowed_book(tab_book, p_nb_book_in_library, perso_connect, p_nb_book_borrowed, nb_max_book_borrowed); 
            }
            else{
                printf("\n You already own 5 books \n");
                printf("\n Please return one before borrowing another :) \n");
            }
            break;

            case 3 :
            // if the person already borrowed books they will be display
            if (*p_nb_book_borrowed>0){
                printf("\n You have borrowed %d book(s) \n", *p_nb_book_borrowed);
                printf("\n You have already borrowed the following book(s) : \n");
                show_book_borrowed(perso_connect, p_nb_book_borrowed);
                printf("\n");
                // function use to return a book
                return_book(tab_book, p_nb_book_in_library, perso_connect, p_nb_book_borrowed);
            }
            else{
                printf("\nYou have not borrowed any books\n");
                printf(" Please borrow one before returning another :) \n");
            }
            break;

            case 4 :
            if (*p_nb_book_borrowed > 0){
                show_book_borrowed(perso_connect, p_nb_book_borrowed);
                printf("\n");
            }
            else{
                printf("\n You have not borrowed any books \n");
            }
            break;

            case 5 :

            // Add a book to the table
            add_a_book(tab_book, p_nb_book_in_library); 

            //allows you to enlarge the book array
            tab_book = (Book *) realloc(tab_book, sizeof(Book));
            file_transfer_to_table(tab_book, p_nb_book_in_library, "library.txt");

            // i = index of books in .book_borrowed (array)
            for (int i= 0; i< *p_nb_book_borrowed; i++){

                // j = index of books in tab_book (array)
                for (int j= 0; j< *p_nb_book_in_library; j++){
                    if (perso_connect.book_borrowed[i].book.id == tab_book[j].id){

                        // ' X ' is a mark 
                        // it allows the user to see the disponibility clearly
                        strcpy( tab_book[j].availability , "    X    ");
                    }
                }
            }
            break;

            case 6 :
            printf("\n Goodbye ! \n");
            break;

            default : 

            // If they do not execute someting in the proposition and enter an other number
            printf("\n Please enter a number between 1 and 6 \n");
            break;
        }
    }while(choice!=6);
}

int main(){

    int nb_books = 0;  
    int nb_persons = 0;  
    int *p_nb_persons;      // pointer on integer ( the number of persons in persons.txt)
    int *p_nb_book_in_library;  // pointer on integer ( the number of books in book.txt)
    int choice, i;

    printf("\n");
    line();
    printf("             Application CY BiblioTECH");
    line();
    printf("\n");
    
    nb_persons = how_much_person("person.txt");
    p_nb_persons = &nb_persons;
    nb_books = how_much_book_in_file_text("library.txt");
    p_nb_book_in_library = &nb_books;



    do{
        //  //allocate memory to the various tables and transfer file to table -> function malloc
        Book * tab_book = (Book *)malloc(sizeof(Book)); 
        Person * tab_persons =(Person*)malloc(sizeof(Person));
        Borrow * books_borrowed =  (Borrow *)malloc(5 * sizeof(Borrow));

        // fill in the tables 
        file_transfer_to_table(tab_book, p_nb_book_in_library, "library.txt");
        file_transfer_to_table1(tab_persons, p_nb_persons, "person.txt");

        // connection (login & password OR create an account )
        choice = connection();

        if (choice == 1){
            i = connection_account(tab_persons, p_nb_persons);  //i is the index of the connected person in the table tab_persons
            Person perso_connect = tab_persons[i];         // The connected person is called perso_connect
            perso_connect.book_borrowed= books_borrowed;
            printf("\n");

            if (strcmp( tab_persons[i].roll, "student" ) == 0){   // access student session

                student_session(perso_connect, tab_book, p_nb_book_in_library);
            }
            if (strcmp( tab_persons[i].roll, "teacher" ) == 0){        // access teacher session
                teacher_session(perso_connect, tab_book, p_nb_book_in_library);
            }
        }

        if (choice == 2){
            create_account(tab_persons, p_nb_persons);
            (*p_nb_persons)++;

             //  Add some place in tab_persons in order to add a new account
            Person * tab_persons =(Person*)malloc(sizeof(Person));   

            // transfer the new account to the file person.txt in order to know every person who have an access at the library
            file_transfer_to_table1(tab_persons, p_nb_persons, "person.txt");
        }

        if (choice == 3){
            printf("Thanks see you soon");
        }

    }while(choice != 3);
    //free(tab_book);
    //free(tab_personnes);
    return 0;
}