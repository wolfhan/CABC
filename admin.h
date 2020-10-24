#include "common.h"

/* Put book on shelf and return whether it is successful or not. 
   Insert the book info into file if on shelf, otherwise do nothing.*/
int putbookonshelf(struct book);

/* Put book off shelf and return whether it is successful or not.
   Remove the book info from file if off shelf, otherwise do nothing. */
int putbookoffshelf(char *);

/* Query all book info from file and save into book array, NULL if
   there is no book in file. */
struct book *queryallbooks();
