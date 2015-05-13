#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int PATH_MAX = 100;

int main(int argc, char const *argv[]) 
{
	char* cwd;
	char buff[PATH_MAX + 1];
	cwd = getcwd(buff, PATH_MAX + 1);
	if( cwd != NULL ) {
		printf("%s>\n", cwd );
	}
	return 0;
}
