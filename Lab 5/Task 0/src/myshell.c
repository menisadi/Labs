#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "LineParser.h"

int PATH_MAX = 100; /*can I delete this?*/

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
    cmdLine* newLine = parseCmdLines(input);
    if (newLine != NULL)
    	printf("argument[0] is : %s\n", newLine->arguments[0]);
	return 0;
}