#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	if (argv[1] == NULL)
		printf("Nothing to say\n");	
	else
		printf("%s\n", argv[1]);
	return 0;
}