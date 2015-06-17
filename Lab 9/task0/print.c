#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "elf.h"

int foreach_phdr(void *map_start, void (*func)(Elf32_Phdr *,int), int arg)
{
	Elf32_Ehdr *elfHeader =  (Elf32_Ehdr *)map_start;


	Elf32_Phdr *programHeader=(Elf32_Phdr*)(  map_start  + elfHeader->e_phoff);
	

	int i =0;
	
	for(;i<elfHeader->e_phnum; ++i)
	{
		func(programHeader,arg);
		programHeader++;
	}
	return 0;
}

void program_headers(Elf32_Phdr *programHeader,int arg){
	/*Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align*/
	printProgramType(programHeader,arg);

	printf("%10x ",programHeader->p_offset);
	printf("%10x ",programHeader->p_vaddr);
	printf("%10x ",programHeader->p_paddr);
	printf("%10x ",programHeader->p_filesz);
	printf("%10x ",programHeader->p_memsz);
	printProgramFlags(programHeader,arg);
	printf("%10x ",programHeader->p_align);




	printf("\n" );




}	
void printProgramFlags(Elf32_Phdr *programHeader,int arg){


	switch(programHeader->p_flags)
	{
		case PF_X:
		printf("%5s","E");
		break;
		case PF_W:
		printf("%5s","W");
		break;
		case PF_X+PF_W:
		printf("%5s","W E");
		break;
		case PF_R:
		printf("%5s","R");
		break;
		case PF_R+PF_X:
		printf("%5s","RE");
		break;
		case PF_W+PF_R:
		printf("%5s","RW");
		break;
		case PF_R+PF_X+PF_W:
		printf("%5s","R W E");
		break;
		default:
		printf("%5s","???");
		break;
	}


}










void printProgramType(Elf32_Phdr *programHeader,int arg){


	switch(programHeader->p_type)
	{
		case PT_NULL:
		printf("%-10s ","NULL");
		break;
		case PT_LOAD:
		printf("%-10s ","LOAD");
		break;
		case PT_DYNAMIC:
		printf("%-10s","DYNAMIC");
		break;
		case PT_INTERP:
		printf("%-10s","INTERP");
		break;
		case PT_NOTE:
		printf("%-10s ","NOTE");
		break;
		case PT_SHLIB:
		printf("%-10s ","SHLIB");
		break;
		case PT_PHDR:
		printf("%-10s ","PHDR");
		break;
		case PT_GNU_STACK:
		printf("%-10s ","GNU_STACK");
		break;
		default:
		printf("%-10s "," ");
		break;
	}


}






int main(int argc, char **argv){
	int fd;
   void *map_start; /* will point to the start of the memory mapped file */
   struct stat fd_stat; /* this is needed to  the size of the file */
   Elf32_Ehdr *header; /* this will point to the header structure */
	int num_of_section_headers;

	if( (fd = open(argv[1], O_RDWR)) < 0 ) {
		perror("error in open");
		exit(-1);
	}

	if( fstat(fd, &fd_stat) != 0 ) {
		perror("stat failed");
		exit(-1);
	}

	if ( (map_start = mmap(0, fd_stat.st_size, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0)) <0 ) {
		perror("mmap failed");
		exit(-4);
	}


	foreach_phdr(map_start,*program_headers,0);






   /* now, we unmap the file */
	munmap(map_start, fd_stat.st_size);
	return 1;
}

