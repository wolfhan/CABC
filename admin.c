#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

/* Allocate buffer for struct book node. */
struct book *balloc() {
    return (struct book *) malloc(sizeof(struct book));
}

/* Put book on shelf and return whether it is successful or not.
   Insert the book info into file if on shelf, otherwise do nothing.*/
int putbookonshelf(struct book b) {
    if (b.name == NULL || b.total == 0) {
        printf("can't put on book that does not have name or total is empty.\n");
        return -1;
    }
    struct book *bp = queryallbooks();
    int found = findbookbyname(bp, b.name);
    if (found == 0) {
        printf("can't put duplicate book on.\n");
        return -2;
    } else {
        return savebookwithbook(bp, b);
    }
}

/* Put book off shelf and return whether it is successful or not.
   Remove the book info from file if off shelf, otherwise do nothing. */
int putbookoffshelf(char *name) {
    struct book *bp = queryallbooks();
    if (bp == NULL) {
        printf("can't remove book from empty books.\n");
        return -1;
    } else {
        int r = findbookbyname(bp, name);
        if (r < 0) {
            printf("can't remove book that does not exist.\n");
            return -2;
        }
        bp = removebook(bp, name);
        
        FILE *fp;
        if ((fp = fopen("bookinfo", "w")) != NULL) {
            if (bp != NULL)
                for (; bp != NULL; bp = bp->next)
                    fprintf(fp, "%s; %d; %d;\n", bp->name, bp->total, bp->left);
            fclose(fp);
            return 0;
        } else {
            printf("bookinfo file can't be opened in putbookoffshelf function.\n");
            return -1;
        }
    }
}

/* Query all book info from file and save into book array, NULL if
   there is no book in file. */
struct book *queryallbooks() {
    FILE *fp;
    fp = fopen("bookinfo", "r");
    if (fp == NULL) {
        return NULL;
    } else {
        char line[MAXLEN];
        char *str;
        struct book *bp;
        bp = NULL;
        while ((str = fgets(line, MAXLEN, fp)) != NULL) {
            char *name;
            int total;
            int left;
            char *token = strtok(str, ";");
            if (token != NULL) {
                name = token;
                token = strtok(NULL, ";");
            } else
                continue;
            if (token != NULL) {
                total = atoi(token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                left = atoi(token);
            }
            struct book b;
            b.name = name;
            b.total = total;
            b.left = left;
            bp = addbook(bp, b);
        }
        fclose(fp);
        return bp;
    }
}

/* Find book info by book name, Return 0 if the book is found, otherwise negative digit. */
int findbookbyname(struct book *bp, char *name) {
    if (bp != NULL) {
        for (; bp != NULL; bp = bp->next) {
            if (strcmp(bp->name, name) == 0)
                return 0;
        }
        return -1;
    } else {
        return -1;
    }
}

/* Save book into bookinfo file. Return 0 if the book is saved, otherwise negative digit. */
int savebook(struct book *bp) {
    FILE *fp;
    if ((fp = fopen("bookinfo", "w")) != NULL) {
        for (; bp != NULL; bp = bp->next)
            fprintf(fp, "%s; %d; %d;\n", bp->name, bp->total, bp->left);
        fclose(fp);
        return 0;
    } else {
        printf("bookinfo file can't be opened in savebook function.\n");
        return -1;
    }
}

/* Save book into bookinfo file. Return 0 if the book is saved, otherwise negative digit. */
int savebookwithbook(struct book *bp, struct book b) {
    if (bp != NULL) {
        int found = 0;
        struct book *bk;
        for (bk = bp; bk != NULL; bk = bk->next) {
            if (strcmp(b.name, bk->name) == 0) {
                found = 1;
            }
        }
        if (found == 0)
            bp = addbook(bp, b);
        else
            return -2;
    } else
        bp = addbook(bp, b);

    FILE *fp;
    if ((fp = fopen("bookinfo", "w")) != NULL) {
        for (; bp != NULL; bp = bp->next)
            fprintf(fp, "%s; %d; %d;\n", bp->name, bp->total, bp->left);
        fclose(fp);
        return 0;
    } else {
        printf("bookinfo file can't be opened in savebookwithbook function.\n");
        return -1;
    }
}

/* Add book node into book node list. */
struct book *addbook(struct book *bp, struct book b) {
    if (bp == NULL) {
        bp = balloc();
        bp->name = strdup(b.name);
        bp->total = b.total;
        bp->left = b.left;
        bp->next = NULL;
    } else
        bp->next = addbook(bp->next, b);
    return bp;
}

/* Remove book node from book node list */
struct book *removebook(struct book *bp, char *name) {
    if (bp == NULL)
        return NULL;
    struct book *bk = bp;
    if (strcmp(bp->name, name) == 0) {
        bk = bp->next;
        free(bp);
        bp = bk;
    } else 
        bp->next = removebook(bp->next, name);
    return bp;
}

/* Add one book */
struct book *addbookbyone(struct book *bp, char *name) {
    if (bp != NULL) {
        if (strcmp(bp->name, name) == 0) {
            if (bp->left < bp->total)
                bp->left++;
        } else
            addbookbyone(bp->next, name);
    }
    return bp;
}

/* Remove one book */
struct book *removebookbyone(struct book *bp, char *name) {
    if (bp != NULL) {
        if (strcmp(bp->name, name) == 0) {
            if (bp->left > 0)
                bp->left--;
        } else
            removebookbyone(bp->next, name);
    }
    return bp;
}
