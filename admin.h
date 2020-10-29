#define MAXLEN 1000
#define MAXBOOK 10000

/* book node  */
struct book {
    char *name;        // book name
    int total;         // total count of this book
    int left;          // left count of this book that is not rented
    struct book *next; // next book node
};

/* Alloc buffer to book node. */
struct book *balloc();

/* Put book on shelf and return whether it is successful or not. 
   Insert the book info into file if on shelf, otherwise do nothing.*/
int putbookonshelf(struct book b);

/* Put book off shelf and return whether it is successful or not.
   Remove the book info from file if off shelf, otherwise do nothing. */
int putbookoffshelf(char *name);

/* Query all book info from file and save into book array, NULL if
   there is no book in file. */
struct book *queryallbooks();

/* Find book from bookinfo file by book name */
int findbookbyname(struct book *bp, char *name);

/* Save book into bookinfo file*/
int savebook(struct book *bp);

/* Save book into bookinfo file*/
int savebookwithbook(struct book *bp, struct book b);

/* Add book into book node list */
struct book *addbook(struct book *bp, struct book b);

/* Remove book from book node list */
struct book *removebook(struct book *bp, char *name);

/* Add one book */
struct book *addbookbyone(struct book *bp, char *name);

/* Remove one book */
struct book *removebookbyone(struct book *bp, char *name);
