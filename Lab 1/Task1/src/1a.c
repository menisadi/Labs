#include<stdio.h>

int main(int argc, char *argv[])
{
	char c; 
	int counter = 1;
 	while ((c = getchar()) != EOF) 
	{
		if (counter == 1) 
		{
			printf("%i : ", counter);
			counter++;
		}
			
		switch(c) 
		{
			case '@' :
				printf("%c\n", c);
				printf("%i : ", counter);
				counter++;
				break;
			case '*' :
				printf("%c\n", c);
				printf("%i : ", counter);
				counter++;
				break;
			default :
				printf("%c", c);
		}
	}
	return 0;
}