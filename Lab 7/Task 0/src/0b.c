#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <unistd.h>
#include <string.h>
  
#define buffer_size 4096

void mem_display(char *filename, int size, void *mem_buffer) {
  printf("mem_display\n");

  char* mem_address;
  int length;
  unsigned int address;
 /*mem_buffer = "1234567890";*/

      do {
        printf( "%s \n","Please enter <address> <length> ");
      } while (scanf("%x %d", &address, &length)!=2);
     
      if (!address)
        address = (unsigned int) mem_buffer;

      mem_address = (char*) address;

      int  i = 0;
      for(; i< length*size; i++ ) {      
        printf("%02hhX", *(mem_address + i));
        if ((i + 1) % size == 0)
          printf(" ");
      }
      printf("\n");
}

void load_into_memory(char *filename, int size, void *mem_buffer) {
  printf("load_into_memory\n");
    
  unsigned int mem_address;
  

  char source_file[100] ={'\0'};


  unsigned int location;
  unsigned int length;

  char line[100] ;

  printf( "\n %s \n","Please enter <mem-address> <source-file> <location> <length> ");
  

  fgets(line ,sizeof(line), stdin );

  sscanf(strtok(line, " "),"%x", &mem_address);
  sscanf(strtok(NULL, " "),"%s", source_file);
  sscanf(strtok(NULL, " "),"%x", &location);
  sscanf(strtok(NULL, " "),"%d", &length);



 /* do {
        printf( "%s \n","Please enter <mem-address> <source-file> <location> <length> ");
      } while (scanf("%x %[^/]/%x %d", &mem_address, &source_file,&location,&length)!=4);
     
*/
  printf("print vars: %x %s %x %d \n", mem_address, source_file,location,length);
  FILE* fp;
  if( (fp = fopen(source_file,"r+")) == NULL){

    printf("%s\n", "can not open" );
    exit(-1);
}
 
  fseek(fp,location,SEEK_SET);
  
  if(mem_address ==0){
    mem_address = (unsigned int)mem_buffer;
  }
  char *arr =(char *)mem_address;

  int i=0;
  printf("\n");
  for(; i < size*length;i++){
    arr[i]  =fgetc(fp);
    printf("%02x ", arr[i]);
  }
  printf("\n");
  printf("Loaded %d units into%02hhX\n", length ,mem_address);

mem_display(filename, size, mem_buffer);
/*
0 abc 12F 10
*/
  



  
  
}
}

void save_into_file(char *filename, int size, void *mem_buffer) {
  printf("save_into_file\n");
  char line[100] = {0};
  unsigned int file_size, s_address, t_location;
  mem_buffer = ";";
  int length;
  char* mem_address;
  FILE* fp = fopen(filename,"r+");

  do {
    printf( "%s \n","Please enter <s-address> <t-location> <length> ");
  } while (scanf("%x %x %d", &s_address, &t_location, &length)!=3);
  printf("\nEnter file name (optional)\n");
  fgets(line ,sizeof(line), stdin); 
  if (line[0] != '\n') {
    fp = fopen(line,"r+");
  }

  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);

  if (file_size < t_location) {
    printf("Error - Offset larger than file size\n");
  }
  else {
    /*fseek(fp, 0L, SEEK_SET);*/
    if (!s_address)
      s_address = (unsigned int) mem_buffer;
    mem_address = (char*) s_address;

    fseek(fp,t_location,SEEK_SET);
    fwrite(mem_address,size,length,fp);
  }
}

void mem_modify(char *filename, int size, void *mem_buffer) {
  printf("Mem Modify\n");

  char* mem_address;
  unsigned int address;
  int val;
  mem_buffer = "1234567890";

  do {
    printf( "%s \n","Please enter <address> <val>");
  } while (scanf("%x %d", &address, &val)!=2);
  printf("%d\n", val);
  if (!address)
    address = (unsigned int) mem_buffer;
  mem_address = (char*) address;
  *mem_address = val;
  printf("%s\n", (char*) mem_buffer);
  printf("\n");
}

void quit(char *filename, int size, void *mem_buffer) {
  exit(0);
}

struct fun_desc {
  char *name;
  void (*fun)(char *filename, int size, void *mem_buffer);
} fun_desc;

int main(int argc, char **argv){
  
  if (argc == 1){
    printf("argc == 1\n");
    exit(EXIT_FAILURE);

  }
  
  char mem_buffer[buffer_size];
  int menuSize = 1;
  char* fileName = argv[1]; 

  int unitSize ;

  if (argc == 3){
    unitSize = atoi(argv[2]);
  }else{
    unitSize = 1;
  }

  struct fun_desc menu[] = {{NULL,NULL},{"Mem Display",mem_display},{"Load Into Memory",load_into_memory},
                          {"Save Into File",save_into_file},{"Mem Modify", mem_modify}, {"Quit",quit},{NULL,NULL}};

  printf("file: %s, buffer location: %p, choose action:\n", fileName, &mem_buffer);
  while (menu[menuSize].name != NULL) {
    printf("%i) %s\n", menuSize, menu[menuSize].name);
    menuSize++;
  }

  int numberCall;

  if (scanf("%d",&numberCall) != 1) {   
    printf("You did not enter a valid number\n");
    /*scanf("%*s");*/
    exit(0);
  }

  if (numberCall > 4 || numberCall < 1) {         /* ascii: 48=0 51=3*/
    printf("invalid choice\n");
    exit(0);
  }

  menu[numberCall].fun(fileName, unitSize, mem_buffer);

/*
  printf("file: %s, buffer location: %x, choose action:\n", fileName, &buffer);
  char c = fgetc(stdin);
  if (c > 51 || c < 48) {         // ascii: 48=0 51=3
    printf("invalid choice\n");
    exit(0);
  }
  printf("\n");
  while (1) {
    (carray.menu[atoi(&c)].fun)(fileName,unitSize);
    menuSize = 0;
    printf("file: %s, buffer location: %x, choose action:\n", fileName, &buffer);
    while (menu[menuSize].name != NULL) {
      printf("%i) %s\n", menuSize, menu[menuSize].name);
      menuSize++;
    }
    c = fgetc(stdin);
    if (c > 52 || c < 48) {
      printf("invalid choice\n");
      exit(0);
    }
    printf("\n\n");
  }
  */
  return 0;
}
  