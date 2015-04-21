#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int iarray[3];
char carray[3];

int main () {
	int iarray[] = {1,2,3};
	char carray[] = {'a','b','c'};
	int* iarrayPtr = iarray;
	char* carrayPtr = carray;
	char* p;
	printf("%p\n",p);
	int i;
	for (i = 0; i < 3; i++)
		printf("%d\n",*(iarrayPtr + i));
	for (i = 0; i < 3; i++)
		printf("%c\n",*(carrayPtr + i));
	return 0;
}