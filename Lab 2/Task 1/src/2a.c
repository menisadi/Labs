#include <stdio.h>
 
char censor(char c) {
  if(c == '!')
    return '.';
  else if(c == 0)
    return 0;
  
  return c;
}
 
void for_each(char *array, char (*f) (char)){
  int i = 0;
  while (*(array+i) != '0') {
  	*(array+i) = f(*(array+i));
  	i++;
  }
}
 
int main(int argc, char **argv){
	char c[] = {'H','E','Y','!', 0};
	for_each(c, censor);
	printf("%s\n", c);
	return 0;
}