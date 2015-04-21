#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char c; 
	int counter = 1;

	char special = -1;
	int doDigit = 0;
	int doFile = 0;
	int i;
	char* fileName;

	for (i = 1; i < argc; i++) 
	{
		if (strcmp(argv[i],"-s") == 0) 
		{
			i++;
			special = *argv[i];
		}
		else if (strcmp(argv[i],"-d") == 0) 
		{
			doDigit = 1;
		}
		else if (strcmp(argv[i],"-i") == 0) 
		{
			doFile = 1;	
			i++;
			fileName = argv[i];
		}
		else
			printf("invalid parameter - %s\n",argv[i]);
	}	

	FILE* input = stdin;
	if (doFile == 1)
		input = fopen(fileName, "r");

 	while ((c = fgetc(input)) != EOF) 
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

				printf("%c\n", c);
				printf("%i : ", counter);
				counter++;
				break;
			default :
				if (c == special)
				{
					printf("%c\n", c);
					printf("%i : ", counter);
					counter++;
				}
				else if (doDigit == 1 && c < 58 && c > 47) 
				{
					printf("%c\n", c);
					printf("%i : ", counter);
					counter++;
				}
				else
					printf("%c", c);
		}
	}
	if (doFile) 
   		fclose(input);
	return 0;
}