#include <stdio.h>

int countEscapeSequences();
void shrinkBlanks();

int main()
{
  //int number = countEscapeSequences();
  shrinkBlanks();
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
