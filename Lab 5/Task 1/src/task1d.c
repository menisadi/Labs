#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "LineParser.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct record
{
    cmdLine* line;
    struct record* next;
} record;

int PATH_MAX = 100; /*can I delete this?*/
record* history = NULL;

void printHistory(record * curr) {
    if (curr != NULL) {
        printHistory(curr->next);
        int i;
        for (i = 0; i < curr->line->argCount; i++)
            printf("%s ", curr->line->arguments[i]);
        printf("\n");
    }
}

void execute(cmdLine *pCmdLine) {
    pid_t pid;
    int i;
    if (strcmp(pCmdLine->arguments[0],"quit") == 0) {
      exit(0);  
    }
    if (strcmp(pCmdLine->arguments[0],"cd") == 0) {
        int err = chdir(pCmdLine->arguments[1]);
        if (err) {
            perror("problem in directory");
        }
    }
    if (strcmp(pCmdLine->arguments[0],"history") == 0) {
        printHistory(history);
    }
    else if(!( pid = fork() )) {
        execvp(pCmdLine->arguments[0],pCmdLine->arguments);
        perror("An error has occurred");
        _exit(1);
    }
    if (pCmdLine->blocking == 1) {
        waitpid(pid,&i,0);
    }
}

int main(int argc, char const *argv[])
{
    while(1) {
        record* newRec = malloc(sizeof(record));
        char* cwd;
        char buff[PATH_MAX + 1];
        char input[PATH_MAX + 1];
        cwd = getcwd(buff, PATH_MAX + 1);
        if( cwd != NULL ) {
            printf("%s>", cwd );
        }
        fgets(input,PATH_MAX,stdin);
        /*if (input != NULL)
            printf("input line is : %s", input);*/
        cmdLine* newCmd = parseCmdLines(input);
        newRec->line = newCmd;
        newRec->next = history;
        history = newRec;
        /*if (newCmd != NULL) {
            printf("command name is : %s\n", newCmd->arguments[0]);
        }*/
        execute(newCmd);
    }
    return 0;
}