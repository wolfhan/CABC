#include <stdio.h>
#include <string.h>
#include "student.h"

void testadmin();
void printbooks(struct book *bp);
void teststudent();
void printcheckedoutbooks(struct checkedoutbook *bp);
void adminmenu();
void getbookname(char bookname[]);
int getbookcount();
int getlinec(char s[], int lim);
void studentmenu();
int getstudentno();

int main() {
    while (1) {
        printf("You are a librarian admin or student:\n1: librarian\n2: student\nInput your number: ");
        int role;
        scanf("%d", &role);
        if (role == 1) 
            adminmenu();
        else if (role == 2) 
            studentmenu();
        else 
            printf("Invalid number\n");
        printf("\n");
    }
    return 0;
}

void adminmenu() {
    printf("\n");
    printf("1: put book on shelf\n2: put book off shelf\n3: query all books\n4: go back\nInput your number: ");
    int option;
    scanf("%d", &option);
    if (option == 1) {
        char bookname[MAXLEN];
        getbookname(bookname);
        int bookcount = getbookcount();
        struct book b;
        b.name = bookname;
        b.total = bookcount;
        b.left = bookcount;
        int result = putbookonshelf(b);
        if (result == 0) 
            printf("Success\n");
        else
            printf("Failure\n");
    } else if (option == 2) {
        char bookname[MAXLEN];
        getbookname(bookname);
        int result = putbookoffshelf(bookname);
        if (result == 0)
            printf("Success\n");
        else
            printf("Failure\n");
    } else if (option == 3) 
        printbooks(queryallbooks());
    else if (option == 4)
        return;
    else {
        printf("Invalid number\n");
    }
    adminmenu();
}

void getbookname(char bookname[]) {
    printf("Input your book name: ");
    getlinec(bookname, MAXLEN);
}

int getlinec(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF; ++i) {
        if (i == 0)
            continue;
        if(c != '\n')
            s[i-1] = c;
        else
            break;
    }
    s[i-1] = '\0';
    char *ss;
    ss = s;
    return i;
}

int getbookcount() {
    printf("Input your book count: ");
    int count;
    scanf("%d", &count);
    return count;
}

void studentmenu() {
    printf("\n");
    printf("1: checkout book\n2: return book\n3: query checked-out books\n4: go back\nInput your number: ");
    int option;
    scanf("%d", &option);
    if (option == 1) {
        int studentno = getstudentno();
        char bookname[MAXLEN];
        getbookname(bookname);
        int result = checkoutbook(studentno, bookname);
        if (result == 0)
            printf("Success\n");
        else
            printf("Failure\n");
    } else if (option == 2) {
        int studentno = getstudentno();
        char bookname[MAXLEN];
        getbookname(bookname);
        int result = returnbook(studentno, bookname);
        if (result == 0)
            printf("Success\n");
        else
            printf("Failure\n");
    } else if (option == 3) {
        int studentno = getstudentno();
        printcheckedoutbooks(querycheckedoutbooks(studentno));
    } else if (option == 4)
        return;
    else {
        printf("Invalid number\n");
    }
    studentmenu();
}

int getstudentno() {
    printf("Input your student_no: ");
    int studentno;
    scanf("%d", &studentno);
    return studentno;
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
    printf("%30s %5s %5s\n", "Book", "Total", "Left");
    if (bp != NULL)
        for (; bp != NULL; bp = bp->next)
            printf("%30s %5d %5d\n", bp->name, bp->total, bp->left);
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
    printf("%-30s\n", "Checked-out Books");
    if (bp != NULL)
        for (; bp != NULL; bp = bp->next)
            printf("%-30s\n", bp->name);
}
