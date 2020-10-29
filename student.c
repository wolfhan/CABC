#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int findcheckedoutbook(struct checkedoutbook *bp, char *bookname);
int savecheckedoutbook(int studentno, struct checkedoutbook *bp);
int savecheckedoutbookwithbook(int studentno, struct checkedoutbook *bp, struct checkedoutbook b);
struct checkedoutbook *addcheckedoutbook(struct checkedoutbook *bp, struct checkedoutbook b);
struct checkedoutbook *removecheckedoutbook(struct checkedoutbook *bp, char *name);

/* Allocate buffer for struct checkedoutbook node. */
struct checkedoutbook *cballoc() {
    return (struct checkedoutbook *) malloc(sizeof(struct checkedoutbook));
}

/* Book is checked out by student. Return 0 if book is checked out, otherwise negative number. */
int checkoutbook(int studentno, char *bookname) {
    struct book *bp = queryallbooks();
    int foundInBookinfo = findbookbyname(bp, bookname);            
    if (foundInBookinfo < 0) {
        printf("%s not in bookinfo file.\n", bookname);
        return -1;
    }
    struct checkedoutbook *cbp = querycheckedoutbooks(studentno);
    int foundCheckedoutBook = findcheckedoutbook(cbp, bookname);
    if (foundCheckedoutBook == 0) {
        printf("%s has been checked out by student %d.\n", bookname, studentno);
        return -2;
    }
    
    bp = removebookbyone(bp, bookname);
    savebook(bp);

    struct checkedoutbook b;
    b.name = bookname;
    b.next = NULL;
    return savecheckedoutbookwithbook(studentno, cbp, b);
}

/* Book is returned by student. Return 0 if book is returned, otherwise negative number. */
int returnbook(int studentno, char *bookname) {
    struct book *bp = queryallbooks();
    int foundInBookinfo = findbookbyname(bp, bookname);
    if (foundInBookinfo < 0) {
        printf("%s not in bookinfo file.\n", bookname);
        return -1;
    }
    struct checkedoutbook *cbp = querycheckedoutbooks(studentno);
    int foundCheckedoutBook = findcheckedoutbook(cbp, bookname);
    if (foundCheckedoutBook < 0) {
        printf("%s has been not checked out by student %d\n.", bookname, studentno);
        return -2;
    }
    
    bp = addbookbyone(bp, bookname);
    savebook(bp);

    cbp = removecheckedoutbook(cbp, bookname);
    return savecheckedoutbook(studentno, cbp);
}

/* Query all checked-out books by student. Return all checked-out books by the student, otherwise NULL. */
struct checkedoutbook *querycheckedoutbooks(int studentno) {
    char bookfilename[50];
    char *bkfilename = bookfilename;
    sprintf(bkfilename, "%d", studentno);

    FILE *fp;
    fp = fopen(bkfilename, "r");
    if (fp == NULL) {
        return NULL;
    } else {
        char line[MAXLEN];
        char *str;
        struct checkedoutbook *bp;
        bp = NULL;
        while ((str = fgets(line, MAXLEN, fp)) != NULL) {
            char *name;
            char *token = strtok(str, ";");
            if (token != NULL) {
                name = token;
                token = strtok(NULL, ";");
            } else
                continue;
            struct checkedoutbook b;
            b.name = name;
            bp = addcheckedoutbook(bp, b);
        }
        fclose(fp);
        return bp;
    }
}

/* Find checked-out book in some student's checkout book file. Return 0 if found, otherwise negative number. */
int findcheckedoutbook(struct checkedoutbook *bp, char *bookname) {
    if (bp != NULL) {
        for (; bp != NULL; bp = bp->next) {
            if (strcmp(bp->name, bookname) == 0)
                return 0;
        }
        return -1;
    } else {
        return -1;
    }
}

/* Save checked-out book into file. Return 0 if the book is saved, otherwise negative digit. */
int savecheckedoutbook(int studentno, struct checkedoutbook *bp) {
    char bookfilename[50];
    char *bkfilename = bookfilename;
    sprintf(bkfilename, "%d", studentno);

    FILE *fp;
    if ((fp = fopen(bkfilename, "w")) != NULL) {
        for (; bp != NULL; bp = bp->next)
            fprintf(fp, "%s;\n", bp->name);
        fclose(fp);
        return 0;
    } else {
        printf("%s file can't be opened in savebook function.\n", bkfilename);
        return -1;
    }
}

/* Save checked-out book into file. Return 0 if the book is saved, otherwise negative digit. */
int savecheckedoutbookwithbook(int studentno, struct checkedoutbook *bp, struct checkedoutbook b) {
    if (bp != NULL) {
        int found = 0;
        struct checkedoutbook *bk;
        for (bk = bp; bk != NULL; bk = bk->next) {
            if (strcmp(b.name, bk->name) == 0) {
                found = 1;
            }
        }
        if (found == 0)
            bp = addcheckedoutbook(bp, b);
        else
            return -2;
    } else
        bp = addcheckedoutbook(bp, b);

    char bookfilename[50];
    char *bkfilename = bookfilename;
    sprintf(bkfilename, "%d", studentno);

    FILE *fp;
    if ((fp = fopen(bkfilename, "w")) != NULL) {
        for (; bp != NULL; bp = bp->next)
            fprintf(fp, "%s;\n", bp->name);
        fclose(fp);
        return 0;
    } else {
        printf("%s file can't be opened in savebook function.\n", bkfilename);
        return -1;
    }
}

/* Add checked-out book into book node list. */
struct checkedoutbook *addcheckedoutbook(struct checkedoutbook *bp, struct checkedoutbook b) {
    if (bp == NULL) {
        bp = cballoc();
        bp->name = strdup(b.name);
        bp->next = NULL;
    } else
        bp->next = addcheckedoutbook(bp->next, b);
    return bp;
}

/* Remove checked-out book from book node list */
struct checkedoutbook *removecheckedoutbook(struct checkedoutbook *bp, char *name) {
    if (bp == NULL)
        return NULL;
    struct checkedoutbook *bk = bp;
    if (strcmp(bp->name, name) == 0) {
        bk = bp->next;
        free(bp);
        bp = bk;
    } else
        bp->next = removecheckedoutbook(bp->next, name);
    return bp;
}

