#include <stdio.h>
#include "student.h"

void testadmin();
void printbooks(struct book *bp);
void teststudent();
void printcheckedoutbooks(struct checkedoutbook *bp);

int main() {
    testadmin();
    teststudent();
    return 0;
}

void testadmin() {
    struct book b;
    b.name = "the c programming language";
    b.total = 10;
    b.left = 10;

    struct book b1;
    b1.name = "Advanced Programming in the UNIX Environment";
    b1.total = 100;
    b1.left = 90;

    int re = putbookonshelf(b);
    printf("re=%d\n", re);
    re = putbookonshelf(b1);
    printf("re=%d\n", re);
    re = putbookoffshelf("Advanced Programming in the UNIX Environment");
    printf("re=%d\n", re);
    struct book *bp = queryallbooks();
    printbooks(bp);
}

void printbooks(struct book *bp) {
    if (bp != NULL)
        for (; bp != NULL; bp = bp->next)
            printf("%s %d %d\n", bp->name, bp->total, bp->left);
}

void teststudent() {
    struct checkedoutbook b;
    b.name = "the c programming language";

    int studentno = 1;
    int re = checkoutbook(studentno, "the c programming language");
    printf("re=%d\n", re);
    re = returnbook(studentno, "the c programming language");
    printf("re=%d\n", re);
    struct checkedoutbook *bp = querycheckedoutbooks(studentno);
    printcheckedoutbooks(bp);
}

void printcheckedoutbooks(struct checkedoutbook *bp) {
    if (bp != NULL)
        for (; bp != NULL; bp = bp->next)
            printf("%s\n", bp->name);
}
