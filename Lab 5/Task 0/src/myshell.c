#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "LineParser.h"
#include <string.h>

int PATH_MAX = 100; /*can I delete this?*/

void execute(cmdLine *pCmdLine) {
    if (strcmp(pCmdLine->arguments[0],"quit") == 0) {
      exit(0);  
    }
    execvp(pCmdLine->arguments[0],pCmdLine->arguments);
    perror("An error has occurred");
}

int main(int argc, char const *argv[])
{
    while(1) {
        char* cwd;
        char buff[PATH_MAX + 1];
        char input[PATH_MAX + 1];
        cwd = getcwd(buff, PATH_MAX + 1);
        if( cwd != NULL ) {
            printf("%s/", cwd );
        }
        fgets(input,PATH_MAX,stdin);
        if (input != NULL)
            printf("input line is : %s", input);
        cmdLine* newCmd = parseCmdLines(input);
        if (newCmd != NULL)
        	printf("command name is : %s\n", newCmd->arguments[0]);
        execute(newCmd);
    	execute(newCmd);
        free(newCmd);
    }
    return 0;
}