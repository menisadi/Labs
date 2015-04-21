#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
	int iarray[3];
	char carray[3];

	printf("iarray address :  %p\n",iarray);
	printf("iarray+1 address :  %p\n",iarray+1);
	printf("carray address :  %p\n",carray);
	printf("carray+1 address :  %p\n",carray+1);
	return 0;
}