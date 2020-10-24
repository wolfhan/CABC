struct book {
    char *name;        // book name
    int total;         // total count of this book
    int left;          // left count of this book that is not rented
    struct book *next; // next book node
};

/* Alloc buffer to book node. */
struct book * balloc();
