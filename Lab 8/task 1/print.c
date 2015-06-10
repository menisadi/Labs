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


int notElf(Elf32_Ehdr *header) {
	if (header->e_ident[0] == 0x7f && header->e_ident[1] == 'E' 
							&& header->e_ident[2] == 'L' && header->e_ident[3] == 'F') {
	printf("\nIs an ELF file\n");
	return 0;
	}
	return 1;
}

int main(int argc, char **argv){
	void *map_start = NULL;
	struct stat fd_stat;
	Elf32_Ehdr *header;
	int fd = -1;
	int statFailure = 0;
	Elf32_Shdr* sectionTable = NULL;
	Elf32_Shdr* current_section = NULL;
	int no_of_sections = 0;
	int index = 0;
	
	fd = open(argv[1] , O_RDWR);
	if ( fd == -1) {
		perror("\nCould not open file.\n");
		_exit(errno);
	}
		
	statFailure = fstat(fd , &fd_stat);
	if (statFailure != 0) {
		perror("\nCouldn't fstat.\n");
		_exit(errno);
	}

	
	map_start = mmap( NULL , fd_stat.st_size , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0);
	if ((int)map_start == -1) {
		perror("\nmmap failed\n");
		_exit(errno);
	}
	printf("\nmap_start = %p\n" , map_start);
	header = (Elf32_Ehdr*) map_start;
	printf("\nheader = %p\n" , header);
if (1 == notElf(header)) {
	perror("\nnot an ELF file, terminating...\n");
	_exit(0);
}

	no_of_sections = header->e_shnum;
	printf("\nNumber of sections: %d\n" , no_of_sections);
	
	sectionTable = (Elf32_Shdr*)((unsigned int)header + (header->e_shoff));
	
	printf("\nthe section table starts at %x\n" , (unsigned int)sectionTable);
	
	current_section = (Elf32_Shdr*)sectionTable;
	/*
	printf("\n%x\n" , current_section->sh_addr);
	*/
	
	Elf32_Shdr* section_header_string_table = &sectionTable[header->e_shstrndx];
	void* section_header_string_table_pointer = map_start + section_header_string_table->sh_offset;
	
	/*
	Elf32_Shdr* sh_strtab = &shdr[header->e_shstrndx];
	const char* const sh_strtab_p = p + sh_strtab->sh_offset;
	*/
	
/* task specification: [index] section_name section_address section_offset section_size */
	printf("%-6s%-18s%-10s%-10s%-10s \n \n" , "idx" , " name" , "address" , "offset" , "size");
	for (index = 0; index<no_of_sections; ++index) {
		printf("#%3d: " , index);/* index */
		printf("%-15s",(char*)(section_header_string_table_pointer + sectionTable[index].sh_name));
		printf("%10x" , current_section->sh_addr);/* address */
		printf("%10x" , current_section->sh_offset);/* offset */
		printf("%10x\n" , current_section->sh_size); /* size */
		current_section = (Elf32_Shdr*)((unsigned int)current_section + (header->e_shentsize));
	}
	
	
	return 1;
}