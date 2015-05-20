#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "LineParser.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int pfd[2];
	pipe(pfd);
	if(!( pid = fork() )) {
    	write[pfd(1)];
        perror("An error has occurred");
        _exit(1);
    }

	read(pfd[0]);
	_exit(1);
	return 0;
}