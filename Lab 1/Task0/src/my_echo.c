#include<stdio.h>

int main(int argc, char *argv[])
{
	int i;
	char* s;
	for(i=1; i < argc; i++ ) 
	{
		s = argv[i];
		printf("%s", s);
		printf(" ");
	}
	return 0;
}
