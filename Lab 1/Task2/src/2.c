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
	int outToFile = 0;
	int numOfFiles = 1;
	int i;
	char* fileName;
	char outfile[256];

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
		else if (strcmp(argv[i],"-o") == 0) 
		{
			outToFile = 1;
			i++;
			numOfFiles = *argv[i]-'0';
		}
		else
			printf("invalid parameter - %s\n",argv[i]);
	}	

	FILE* input = stdin;
	if (doFile == 1)
		input = fopen(fileName, "r");
	char* outputNames[5];
	if (outToFile == 1) {
		int j;
		for (j = 0; j < numOfFiles; j++) {
			printf("Enter output file %d : \n", j+1);
			scanf("%s", outfile);
			/*printf("%s\n", outfile);*/
			outputNames[j] = outfile;
			
			/*output[j] = fopen(outfile, "a");*/
			/*fprintf(output[j],"test 1 \n");*/
			
			/*output[0] = fopen(outfile, "a");*/
			/*fprintf(output[0],"test 1 \n");*/
		}
	}
	
	int j = 0;
	FILE* output = stdout;
 	while ((c = fgetc(input)) != EOF && c != '\n')
	{
		printf("hi1\n");
		if (outToFile) {
			output = fopen(outputNames[j], "a");
			printf("hi2\n");
		}
		if (counter == 1) 
		{
			fprintf(output,"%i : ", counter);
			counter++;
		}
			
		switch(c) 
		{
			case '@' :
				fprintf(output,"%c\n", c);
				j = (j + 1) % numOfFiles;
				fprintf(output,"%i : ", counter);
				counter++;
				break;
			case '*' :
				fprintf(output,"%c\n", c);
				j = (j + 1) % numOfFiles;
				fprintf(output,"%i : ", counter);
				counter++;
				break;

				fprintf(output,"%c\n", c);
				j = (j + 1) % numOfFiles;
				fprintf(output,"%i : ", counter);
				counter++;
				break;
			default :
				if (c == special)
				{
					fprintf(output,"%c\n", c);
					j = (j + 1) % numOfFiles;
					fprintf(output,"%i : ", counter);
					counter++;
				}
				else if (doDigit == 1 && c < 58 && c > 47) 
				{
					fprintf(output,"%c\n", c);
					j = (j + 1) % numOfFiles;
					fprintf(output,"%i : ", counter);
					counter++;
				}
				else {
					fprintf(output,"%c" , c);
					/*printf("test %i %c \n",j, c);*/
				}
		if (outToFile)
			fclose(output);			
		}
	}
	printf("\n");
	if (doFile) 
   		fclose(input);
	return 0;
}