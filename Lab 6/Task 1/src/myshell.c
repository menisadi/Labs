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

typedef struct variable
{
    char* name;
    char* value;
    struct variable* next;
}  variable;

int PATH_MAX = 100; /*can I delete this?*/
record* history = NULL;
variable* variables = NULL;

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

void freeEnv(variable* var) {
    if (var->next != NULL)
        freeEnv(var->next);
    free(var);
}

void addVariable(char* newName, char* newValue) {
    variable* newVar = malloc(sizeof(variable));
    newVar->name = newName;
    newVar->value = newValue;
    newVar->next = variables;
    variables = newVar;
}

char* getSetValue(variable* var, char* name, int set, char* newArg) {
    if (var == NULL)
        return 0;
    if (var->name != NULL && strcmp(var->name,name) == 0) {
        if (set == 1)
            var->value = newArg;
        else if (set == 2)
            var->name = newArg;
        return var->value;
    }
    return getSetValue(var->next,name,set,newArg);
}

int checkVars(cmdLine *pCmdLine) {
    int i;
    int found = 0;
    for (i = 0; i < pCmdLine->argCount; i++)
        if (strncmp(pCmdLine->arguments[i],"$",1) == 0) {
            char* varVal = getSetValue(variables,pCmdLine->arguments[i] + 1,0,"");
            if (varVal == 0)
                printf("Variable - %s - does not exist\n", pCmdLine->arguments[i] + 1);
            else {
                replaceCmdArg(pCmdLine,i,varVal); 
                found = 1;
            }
        }
    return found;         
}

void printEnv(variable* var) {
    if (var->name != NULL)
        printf("name: %s ; value: %s\n", var->name, var->value);
    if (var->next != NULL)
        printEnv(var->next);
}

cmdLine* fixArgs(cmdLine *pCmdLine) {
    char strArgs[100];
    strcpy(strArgs,pCmdLine->arguments[0]);
    int i;
    for (i = 1; i < pCmdLine->argCount; i++) {
        strcat(strArgs, " ");
        strcat(strArgs,pCmdLine->arguments[i]);
    }
    cmdLine* newCmd = parseCmdLines(strArgs);    
    return newCmd;
}

void execute(cmdLine *pCmdLine) {
    pid_t pid;
    
    /*int* inp;
    int* outp;*/

    int foundVar = checkVars(pCmdLine);
    if (foundVar == 1)
        pCmdLine = fixArgs(pCmdLine);

    /* int saveStdin = dup(0);
    int saveStdout = dup(1); */

    /* printf("%s\n", pCmdLine->arguments[0]);*/
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
    else if (strcmp(pCmdLine->arguments[0],"env") == 0) {
        printEnv(variables);
    }
    else if (strcmp(pCmdLine->arguments[0],"set") == 0) {
        if (pCmdLine->argCount < 3)
            printf("Missing parameter\n");    
        else { 
            if (pCmdLine->argCount > 3) {
                int i;
                char str[100];
                strcpy(str, pCmdLine->arguments[2]);
                for (i = 3; i < pCmdLine->argCount; i++) {
                    strcat(str, " ");
                    strcat(str, pCmdLine->arguments[i]);
                }
                replaceCmdArg(pCmdLine,2,str); 
            }
            if (getSetValue(variables,pCmdLine->arguments[1],1,pCmdLine->arguments[2]) == 0)
                addVariable(pCmdLine->arguments[1],pCmdLine->arguments[2]);
        }
    }
    else if(strcmp(pCmdLine->arguments[0],"rename") == 0) {
        if (pCmdLine->argCount < 3)
            printf("Missing parameter\n");    
        else
            if (getSetValue(variables,pCmdLine->arguments[1],2,pCmdLine->arguments[2]) == 0)
                perror("Variable does not exist");
    }
    else if(strcmp(pCmdLine->arguments[0],"delete") == 0) {
        if (pCmdLine->argCount < 2)
            printf("Missing parameter\n");    
        else
            if (getSetValue(variables,pCmdLine->arguments[1],2,NULL) == 0)
                perror("Variable does not exist");
    }
    else if (strcmp(pCmdLine->arguments[0],"history") == 0) {
        printHistory(history);
        return;
    }
    else if(!( pid = fork() )) {
        if (pCmdLine->inputRedirect) {
            fclose(stdin);
            fopen(pCmdLine->inputRedirect, "r");
          }

        if (pCmdLine->outputRedirect) {
            fclose(stdout);
            fopen(pCmdLine->outputRedirect, "w");
        }

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