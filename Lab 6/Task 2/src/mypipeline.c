#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define STDIN 0
#define STDOUT 1
int main(int argc, char const *argv[])
{
  	int pipefd[2];
    pid_t cpid1;
    pid_t cpid2;
    int writeDup =0;
    int readDup =0;
    char* writeLS[] = {"ls", "-l", NULL};
    char* readTail[] = {"tail", "-n", "2", NULL};
    

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    cpid1 = fork();
    
    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (cpid1 == 0) {  
    	
        close(STDOUT);
        writeDup = dup(pipefd[1]);
	    close(pipefd[1]);
        execvp(writeLS[0], writeLS);
        
    }else{
    
    close(writeDup);
    cpid2 = fork();
    if (cpid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (cpid2 == 0) {
    	close(STDIN);
    	readDup = dup(pipefd[0]);
    	close(pipefd[0]);
    	execvp(readTail[0], readTail);
    	
    }else {

    close(readDup);
    
    waitpid(cpid2,NULL,0);
     
}
}
return 0;
}