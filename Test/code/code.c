#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char x[] = {0,1,2,3,4,5,6,7};
	printf("%d\n", sizeof(x));
	char* y = (char*)x;
	printf("%d\n", sizeof(y));
    return 0;
} 
