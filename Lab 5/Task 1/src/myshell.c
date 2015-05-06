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
    int index;
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

cmdLine* callPast(record* past, int i) {
    record* curr = past;
    if (curr->index == i)
        return curr->line;
    return callPast(past->next,i);
}

void freeAll(record * curr) {
    freeCmdLines(curr->line); 
    if (curr->next)
        freeAll(curr->next);    
    free(curr);      
}

void execute(cmdLine *pCmdLine) {
    pid_t pid;
    if (strcmp(pCmdLine->arguments[0],"quit") == 0) {
      freeAll(history);
      _exit(1);  
    }
    if (strcmp(pCmdLine->arguments[0],"cd") == 0) {
        if (pCmdLine->argCount == 1)
            printf("Missing parameter\n");    
        else {
            chdir(pCmdLine->arguments[1]);
            perror("problem in directory");
        }
    }
    if (strcmp(pCmdLine->arguments[0],"history") == 0) {
        printHistory(history);
        return;
    }
    else if(!( pid = fork() )) {
        execvp(pCmdLine->arguments[0],pCmdLine->arguments);
        perror("An error has occurred");
        freeAll(history);
        _exit(1);
    }
    if (pCmdLine->blocking == 1) {
        waitpid(pid,NULL,0);
    }
}

int main(int argc, char const *argv[])
{
    int largeIndex;
    while(1) {
        largeIndex = 0;
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
        if (newCmd->arguments[0][0] == '!') {
            if (history != NULL) {
                int callIndex = newCmd->arguments[0][1] - '0';
                if (callIndex > history->index) {
                    printf("Index out of bound\n");
                    largeIndex = 1;
                }
                else
                    newCmd = callPast(history,callIndex);
                }
            else {
                printf("Index out of bound\n");
                largeIndex = 1;
            }
        }
        newRec->line = newCmd;
        if (history == NULL)
            newRec->index = 0;
        else
            newRec->index = (history->index) + 1;
        newRec->next = history;
        history = newRec;
        /*if (newCmd != NULL) {
            printf("command name is : %s\n", newCmd->arguments[0]);
        }*/
        if (!largeIndex) 
            execute(newCmd);
    }
    freeAll(history);
    return 0;
}