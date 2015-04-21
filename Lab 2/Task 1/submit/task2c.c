#include <stdio.h>
#include <stdlib.h>
 
char censor(char c) {
  if(c == '!')
    return '.';
  else if(c == 0)
    return 0;
  
  return c;
}

/* Gets a character c, and returns it in lower case. 
Characters that do not have a lower case, are returned unchanged */
char to_lower(char c) {
  if (c <= 'Z' && c >= 'A')
    return c+32;
  return c;
}

/* Prints the value of c, followed by a new line, and returns c unchanged */
char cprt(char c) {
  printf("%c\n", c);
  return c;
}

/* Ignores c, reads and returns a character from stdin using fgetc. 
Returns 0 when a new line character is read. */
char my_get(char c) {
  char newC = fgetc(stdin);
  if (newC == '\n') {
    return 0;
  }
  else
    return newC;
}

/* Gets a character c, ignores it, and ends the program */
char quit(char c) {
  exit(0);
}

void for_each(char *array, char (*f) (char)){
  int i = 0;
  while (*(array+i) != 0) {
    *(array+i) = f(*(array+i));
    i++;
  }
}
 
int main(int argc, char **argv){
  char c[5];
  for_each(c, my_get);
  for_each(c, cprt);
  for_each(c, to_lower);
  for_each(c, censor);
  for_each(c, cprt);
  for_each(c, quit);
  return 0;
}