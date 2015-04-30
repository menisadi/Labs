extern int system_call();
#include "util.h"

#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_READ 3
#define SYS_WRITE 4

#define STDIN 0
#define STDOUT 1

int main (int argc , char* argv[], char* envp[])
{
	char c = 1;
	int counter = 1;

	int doFile = 0;
	int outToFile = 0;
	int i;
	char* fileName;
	int numOfFiles;
	char * str;

	for (i = 1; i < argc; i++) 
	{
		if (strcmp(argv[i],"-o") == 0) 
		{
			outToFile = 1;
			i++;
			numOfFiles = positive_atoi(argv[i]);
		}
		else if (strcmp(argv[i],"-i") == 0) 
		{
			doFile = 1;	
			i++;
			fileName = argv[i];
			/*system_call(SYS_WRITE,STDOUT,fileName,strlen(fileName));*/
			/*system_call(SYS_WRITE,STDOUT,"\n",1);*/
		}
		else {
			system_call(SYS_WRITE,STDOUT,"invalid parameter", 17);
			system_call(SYS_WRITE,STDOUT,"\n",1);
		}
	}	
	int files[5];
	if (outToFile == 1) {
		system_call(SYS_WRITE,STDOUT,"Number of output files: ", 24);
		system_call(SYS_WRITE,STDOUT,itoa(numOfFiles),strlen(itoa(numOfFiles)));
		int i;
		char * tmp = "";
		for (i = 0; i < numOfFiles; i++) {
			system_call(SYS_WRITE,STDOUT,"\nEnter output file : ",21);
			system_call(SYS_READ,STDIN,&tmp,15);		
			files[i] = system_call(SYS_OPEN,&tmp,64|2,0777);	
		}

	}

	i = 0;
	int input = STDIN;
	if (doFile == 1) {
		input = system_call(SYS_OPEN,fileName,0,0777);
	}
	int done = 0;	
	/*system_call(SYS_WRITE,STDOUT,"test0\n",6);	*/
	system_call(SYS_READ,input,&c,1);
 	
 	while (!done)
	{		
		if (counter == 1) 
		{
			if (outToFile) {
				/*system_call(SYS_WRITE,STDOUT,"\nTestAA\n",8);*/
				system_call(SYS_WRITE,files[i],"1 : ",3);	
			}
			else {
				/*system_call(SYS_WRITE,STDOUT,"\nTestBB\n",8);*/
				system_call(SYS_WRITE,STDOUT,"1 : ",3);
			}
			counter++;
		}
		/*system_call(SYS_WRITE,STDOUT,"test1\n",6);	*/
		switch(c) 
		{
			case '@' :
				str = itoa(counter);
				if (outToFile) {
					system_call(SYS_WRITE,files[i],&c,1);
					system_call(SYS_WRITE,files[i],"\n",1);
					i = (i+1)%numOfFiles;
					/*system_call(SYS_WRITE,STDOUT, itoa(i), strlen(itoa(i));*/
					system_call(SYS_WRITE,files[i], str, strlen(str));
					system_call(SYS_WRITE,files[i]," : ",3);
				}
				else {
					system_call(SYS_WRITE,STDOUT,&c,1);
					system_call(SYS_WRITE,STDOUT,"\n",1);
					system_call(SYS_WRITE,STDOUT, str, strlen(str));
					system_call(SYS_WRITE,STDOUT," : ",3);
				}
				counter++;
				break;

			case '*' :
				str = itoa(counter);
				if (outToFile) {
					system_call(SYS_WRITE,files[i],&c,1);
					system_call(SYS_WRITE,files[i],"\n",1);
					i = (i+1)%numOfFiles;
					system_call(SYS_WRITE,files[i], str, strlen(str));
					system_call(SYS_WRITE,files[i]," : ",3);
				}
				else {
					system_call(SYS_WRITE,STDOUT,&c,1);
					system_call(SYS_WRITE,STDOUT,"\n",1);
					system_call(SYS_WRITE,STDOUT, str, strlen(str));
					system_call(SYS_WRITE,STDOUT," : ",3);
				}
				counter++;
				break;

			default :
				{
					/*system_call(SYS_WRITE,STDOUT,"test2\n",6);*/
					if (outToFile) {
						system_call(SYS_WRITE,files[i],&c,1);
						/*system_call(SYS_WRITE,STDOUT,"\nTestCC\n",8);*/
					}
					else {
						system_call(SYS_WRITE,STDOUT,&c,1);
						/*system_call(SYS_WRITE,STDOUT,"\nTestDD\n",8);*/
					}
				}
		}
		system_call(SYS_READ,input,&c,1);
		if (c == '\n' || c == '\0') 
			done = 1;
	}
	system_call(SYS_WRITE,STDOUT,"\n",1);
	if (doFile) 
		system_call(SYS_CLOSE,input);
	if (outToFile)
		for (i = 0; i < numOfFiles; i++)
			system_call(SYS_CLOSE,files[i]);
	return 0;
}