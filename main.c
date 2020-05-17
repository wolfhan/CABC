#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int countEscapeSequences();
void shrinkBlanks();
void printEscapeSequences();
void countLineWordChar();
void printOneWordPerLine();
void countCharacters();

int main()
{
    //int number = countEscapeSequences();
    //shrinkBlanks();
    //printEscapeSequences();
    //countLineWordChar();
    //printOneWordPerLine();
    countCharacters();
    return 0;
}

/* count blanks, tabs and lines in input */
int countEscapeSequences()
{
  int c, number;
  number = 0;
  while ((c = getchar()) != EOF)
      if (c == ' ' || c == '\t' || c == '\n')
	  ++number;
  printf("%d\n", number);
  return number;
}

/* Replace more than one blanks by single blank */
void shrinkBlanks()
{
  int c, number = 0;
  while ((c = getchar()) != EOF)
  {
      if (c == ' ')
      {
	++number;
      }
      else
      {
	number = 0;
      }
      if (number <= 1)
      {
	putchar(c);
      }
  }
}

/* Print tab and backspace */
void printEscapeSequences()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            putchar('\\');
  	    putchar('t');	    
        }
	else if (c == '\b')
	{
	    putchar('\\');
	    putchar('b');
	}
	else
	{
	    putchar(c);
	}
    }
}

/* count lines, words, and characters in input */
void countLineWordChar()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
	++nc;
	if (c == '\n')
	    ++nl;
	if (c == ' ' || c == '\n' || c == '\t')
	    state = OUT;
	else if (state == OUT) {
	    state = IN;
	    ++nw;
	}
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/* print one word per line */
void printOneWordPerLine()
{
    int c, state;
    state = OUT;
    while ((c = getchar()) != EOF)
    {
	if (c == ' ' || c == '\n' || c == '\t') {
	    state = OUT;
	    putchar('\n');
        } else if (state == OUT) {
	    state = IN;
	    putchar(c);
	} else {
	    putchar(c);
	}
    }
}

/* count digits, white space, others  */
void countCharacters()
{
    int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
	ndigit[i] = 0;
    while ((c = getchar()) != EOF)
	if (c >= '0' && c <= '9')
	    ++ndigit[c - '0'];
    	else if (c == ' ' || c == '\n' || c == '\t')
	    ++nwhite;
    	else 
	    ++nother;
    printf("digits =");
    for (i = 0; i < 10; ++i)
	printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}
