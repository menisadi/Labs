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
      printf("\n");

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

  char file[100]  ,input_buffer[100];
  unsigned int t_location;

  /*mem_buffer = "NOPNOPNOPNOPNOPNOPbcdefghijklm";*/

  int length;
  FILE* fp;
  unsigned int address;

  printf( "%s \n","Please enter <mem-address> <source-file> <location> <length> ");

  fgets(input_buffer, 100, stdin);
  sscanf(input_buffer, "%x %s %x %d", &address, file, &t_location, &length);
  
  fp = fopen(file,"rb");

  if (!address)
    address = (unsigned int) mem_buffer;

  fseek(fp,t_location,SEEK_SET);
  fread((void *) address, size, length, fp);

  fclose(fp);

  printf("\n");
  printf("Loaded %d units into 0x%x\n", length, address);

  /*mem_display(filename,size,mem_buffer);*/

}

void save_into_file(char *filename, int size, void *mem_buffer) {
  printf("save_into_file\n");
  char line[100] = {0};
  unsigned int file_size, s_address, t_location;
  mem_buffer = "++++++++++abcdefghijklm";
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
  fclose(fp);
}

void mem_modify(char *filename, int size, void *mem_buffer) {
  printf("Mem Modify\n");
  int mem_address;
  unsigned int val;
  char buffer[100]; 
  printf( "%s \n","Please enter <address> <val>");
  fgets(buffer,100,stdin);
  sscanf(buffer, "%x %x", &mem_address, &val);
  /*mem_buffer = "1234567890";*/
  
  if (!mem_address)
    mem_address = (unsigned int) mem_buffer;
  int i;
  for (i = size-1; i >= 0; i--) {
    printf("\n%d\n", val % 256);
    (*((char *)mem_address + i)) = val % 256;
    val = val >> 2;
  }
  printf("\n");
  mem_display(filename,size,mem_buffer);
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

  if (numberCall > 5 || numberCall < 1) {  
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
  