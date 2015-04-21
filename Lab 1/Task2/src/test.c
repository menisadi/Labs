#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE * fp[2];
   fp[0] = fopen ("file1", "a");
   fp[1] = fopen ("file2", "a");
   fprintf(fp[0], "%s %s", "We", "are");
   fprintf(fp[1], "%s %d", "in", 2012);

   fclose(fp[0]);
   fclose(fp[1]);
   return(0);
}