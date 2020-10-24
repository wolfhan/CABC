#include "common.h"

/* Book is checked out by student. */
int checkoutbook(int studentno, char *);

/* Book is returned by student. */
int returnbook(int studentno, char *);

/* Query all checked-out books by student. */
struct book *querycheckedbooks(int studentno);
