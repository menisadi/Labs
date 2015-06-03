#include <stdio.h>
#include <stdlib.h>

#define buffer_size 4000

void mem_display(char *filename, int size, void *mem_buffer) {
  printf("mem_display\n");
}

void load_into_memory(char *filename, int size, void *mem_buffer) {
  printf("load_into_memory\n");
}

void save_into_file(char *filename, int size, void *mem_buffer) {
  printf("save_into_file\n");
}

void quit(char *filename, int size, void *mem_buffer) {
  exit(0);
}

struct fun_desc {
  char *name;
  char (*fun)(char *filename, int size, void *mem_buffer);
} fun_desc;

int main(int argc, char **argv){
  char carray[100] = "mm";
  char buffer[buffer_size];
  int menuSize = 0;
  char* fileName = argv[1];
  int unitSize = 1;
  if (argc == 3)
    unitSize = atoi(argv[2]);
  struct fun_desc menu[] = {{"Mem Display",mem_display},{"Load Into Memory",my_get}
                          ,{"Save Into File",cprt}, {"Quit",quit},{NULL,NULL}};

  while (menu[menuSize].name != NULL) {
    printf("%i) %s\n", menuSize, menu[menuSize].name);
    menuSize++;
  }

  printf("file: %s, buffer location: %x, choose action:\n", fileName, &buffer);
  char c = fgetc(stdin);
  if (c > 51 || c < 48) {         // ascii: 48=0 51=3
    printf("invalid choice\n");
    exit(0);
  }
  printf("\n");
  while (1) {
    (carray,menu[atoi(&c)].fun)(fileName,unitSize);
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
  return 0;
}