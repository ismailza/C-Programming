#include <stdio.h>
#include <stdlib.h>

void inverserChaine()
{
  char c;
  if ((c = getchar()) != '\n')
  {
    inverserChaine();
    printf("%c", c);
  }
}

void main()
{
  printf("\nTaper votre phrase : ");
  inverserChaine();
}