#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "LineParser.h"

int PATH_MAX = 100; /*can I delete this?*/

void execute(cmdLine *pCmdLine) {
    execv(pCmdLine->arguments[0],pCmdLine->arguments);
    printf("An error has occurred\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
	char* cwd;
    char buff[PATH_MAX + 1];
    char input[PATH_MAX + 1];
    cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        printf("%s/", cwd );
    }
    fgets(input,PATH_MAX,stdin);
    if (input != NULL)
    	printf("input line is : %s", input);
    cmdLine* newCmd = parseCmdLines(input);
    if (newCmd != NULL)
    	printf("argument[0] is : %s\n", newCmd->arguments[0]);
	execute(newCmd);
    return 0;
}