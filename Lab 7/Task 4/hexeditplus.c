#include <stdio.h>
#include <stdlib.h>

struct fun_desc {
  char *name;
  void (*fun)(char*, int, void*);
};

void quit(char *filename, int size, void *mem_buffer);
void loadIntoMemory(char *filename, int size, void *mem_buffer);
void saveIntoFile(char *filename, int size, void *mem_buffer);
void memoryDisplay(char *filename, int size, void *mem_buffer);
void memModify(char *filename, int size, void *mem_buffer);

struct fun_desc menu[] = { 
  { "Mem Display", memoryDisplay }, 
  { "Save Into File", saveIntoFile },
  { "Load Into Memory", loadIntoMemory }, 
  { "Mem Modify", memModify },
  { "Quit", quit }, 
  { NULL, NULL } 
};
int bufferSize = 40000;

void print_menu(char * filename, char *buffer) {
  /* Print menu */
  int mItem = 0;
  printf("\nFile: %s, buffer location: %p, choose action:\n", filename, buffer);
  while(1) {
    if (menu[mItem].name == NULL) 
      break;
    printf("%i: %s\n", mItem, menu[mItem].name);
    mItem++;
  }
  printf("Option: ");
}
 
 
int main(int argc, char **argv) {
  char temp_buffer[100];
  
	if (argc < 2) {
		printf("please specify a file to load.\n");
		exit(0);
	}
	
	/* Handle input params */
	char * filename = argv[1];	
	char buffer[40000] = " ";
	int unitSize;

	bufferSize = 40000;
	if (argc > 2) {
		unitSize = (int) atoi(argv[2]); 
	}
	else {
	 unitSize = 1;
  }

	FILE * file = fopen(filename, "r");
  if( file == NULL ) {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }  

 /*fread(buffer, 40000, 1, file);*/
 fclose(file);

  while(1) {
    print_menu(filename, buffer);
    char sel = fgetc(stdin);
    
    fgets(temp_buffer, 100, stdin);
    
    if (sel < '0' || sel > '4') 
      exit(0);
    int selN =  sel - '0';
    printf("\n%i\n", selN);
    (menu[selN].fun)(filename, unitSize, buffer);
  }
  
  return 0;
}

void memoryDisplay(char *filename, int size, void *mem_buffer) {
  int s_address, length;
  int i, j;
  unsigned int digit = 0;
  char format[10];
  char input_buffer[200];
  printf("\nPlease enter <address> <length>\n");
  
  fgets(input_buffer, 200, stdin);
  
  sscanf(input_buffer, "%x %d", &s_address, &length);
 
  unsigned char * location = (unsigned char *) s_address;
  if (s_address == 0) {
  	location = mem_buffer;
  }
  sprintf(format, "%c0%dX ",'%', size*2);

  for (i = 0; i < length*size; i += size) {
    for(j = 0; j < size; j++)
    {
      unsigned char c = *(location + i + j);
      digit = (digit << 8) +  c;
    }
    printf(format, digit);
    digit = 0;
  }
}

void loadIntoMemory(char *filename, int size, void *mem_buffer) {
  int mem_address, location, length;
  char source_file[200], input_buffer[200];
  FILE *file;
  
  printf("Please enter <mem-address> <source-file> <location> <length>\n");
  
  fgets(input_buffer, 200, stdin);
  
  sscanf(input_buffer, "%x %s %x %d", &mem_address, source_file, &location, &length);

  if (mem_address == 0)
    mem_address = (int)mem_buffer;
  
  file = fopen(source_file, "rb");
  fseek(file, location, SEEK_SET);
  fread((void *) mem_address, size, length, file);

  fclose(file);
  
  printf("Loaded %d units into 0x%x\n", length, mem_address);
}


void saveIntoFile(char *filename, int size, void *mem_buffer) {
  int s_address, t_location, length;
  char input_buffer[200];
  FILE *file = fopen(filename, "r+");
  printf("Please enter <s-address> <t-location> <length>\n");
  
  fgets(input_buffer, 200, stdin);
  
  sscanf(input_buffer, "%x %x %d", &s_address, &t_location, &length);
  
  printf("saving to: %x %x %d\n", s_address, t_location, length);
  
  if (s_address == 0)
    s_address = (int)mem_buffer;
  
  fseek(file, t_location, SEEK_SET);
  fwrite((void *) s_address, size, length, file);
  
  fclose(file);
}


/**
 * Ends the program.
 */
void quit(char *filename, int size, void *mem_buffer) {
  exit(0);
}

void memModify(char *filename, int size, void *mem_buffer) {
  int mem_address;
  unsigned int value;
  char input_buffer[200];
  
  printf("Please enter <mem-address> <value>\n");
  
  fgets(input_buffer, 200, stdin);
  
  sscanf(input_buffer, "%x %x", &mem_address, &value);

  if (mem_address == 0)
    mem_address = (int)mem_buffer;

  int j;
  for (j = size -1; j >= 0; j--) {
  	(*((char *)mem_address + j)) = (char) (value % (int) (1 << 8));
  	value = value >> 8;
  }

}