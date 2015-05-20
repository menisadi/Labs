#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>


/*  http://tldp.org/LDP/lpg/node11.html     */



int creatPip(){
  char* line[3]={"ls","-l",NULL};
   char* line2[4]={"tail","-n","2",NULL};
  int fd[2]={0,0};
 if(pipe(fd)!=0){
   printf("error pipe didnt work \n");
   exit(0);
 }
 int pID = fork();
  if(pID==0){
      close(1);
     if( dup(fd[1])==-1){
          printf("error dup fd[1] \n");
	     exit(0);
     }
      close(fd[1]);
       if(execvp(line[0], line)<0){
       perror("error execv didnt work");
        exit(EXIT_FAILURE);}
}
 else {
   if(pID<0){
       perror("error execv didnt work");
        exit(EXIT_FAILURE);}
   
    close(fd[1]);
    int  pID2 = fork();
      if(pID2==0){
      close(0);
   if( dup(fd[0])==-1){
            printf("error dup fd[0] \n");
	     exit(0);
     }
      close(fd[0]);
       if(execvp(line2[0], line2)<0){
       perror("error execv didnt work");
        exit(EXIT_FAILURE);}

} else{
     if(pID2<0){
       perror("error execv didnt work");
        exit(EXIT_FAILURE);}
       close(fd[0]);
        waitpid(pID2,0,0);
    
}
  waitpid(pID,0,0);
  }
  
return 0;
}




int main (int argc , char* argv[], char* envp[]){
creatPip();
  return 0;
  
}