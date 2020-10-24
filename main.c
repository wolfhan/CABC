#include <stdio.h>
#include "admin.h"

void testadmin();
void printbooks(struct book *);

int main() {
    testadmin();
    return 0;
}

void testadmin() {
    struct book *bk;
    bk = NULL;
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
