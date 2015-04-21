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
  char c;
  while ((c = f(*(array)))) {
    *(array) = c;
    array++;
  }
}
 
struct fun_desc {
  char *name;
  char (*fun)(char);
};

int main(int argc, char **argv){
  char carray[100] = "mm";
  struct fun_desc menu[] = {{"To lower",to_lower},{"My get",my_get},{"Cprt",cprt},
              {"Censor",censor},{"Quit",quit},{NULL,NULL}};
  int size = 0;
  while (menu[size].name != NULL) {
    printf("%i) %s\n", size, menu[size].name);
    size++;
  }
  printf("Choose function:\n");
  char c = fgetc(stdin);
  if (c > 52 || c < 48) {
    printf("invalid choice\n");
    exit(0);
  }
  printf("\n");
  while (1) {
    for_each(carray,menu[atoi(&c)].fun);
    size = 0;
    while (menu[size].name != NULL) {
      printf("%i) %s\n", size, menu[size].name);
      size++;
    }
    printf("Choose function:\n");
    c = fgetc(stdin);
    if (c > 52 || c < 48) {
      printf("invalid choice\n");
      exit(0);
    }
    printf("\n\n");
  }
  return 0;
}