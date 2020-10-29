#include "admin.h"

/* checked-out book node */
struct checkedoutbook {
    char *name;                  // checked-out book name
    struct checkedoutbook *next; // next book node
};

/* Alloc buffer to checkedoutbook node*/
struct checkedoutbook *cballoc();

/* Book is checked out by student. */
int checkoutbook(int studentno, char *bookname);

/* Book is returned by student. */
int returnbook(int studentno, char *bookname);

/* Query all checked-out books by student. */
struct checkedoutbook *querycheckedoutbooks(int studentno);
