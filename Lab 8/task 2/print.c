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

int getStrTableOffset (Elf32_Ehdr* header , void* map_start)  {
	Elf32_Shdr* sectionTable = NULL;
	Elf32_Shdr* current_section = NULL;
	int no_of_sections = 0;
	int index = 0;	
	
	no_of_sections = header->e_shnum;
	
	sectionTable = (Elf32_Shdr*)((unsigned int)header + (header->e_shoff));
	
	current_section = (Elf32_Shdr*)sectionTable;
	
	Elf32_Shdr* section_header_string_table = &sectionTable[header->e_shstrndx];
	
	void * section_header_string_table_pointer = map_start + (section_header_string_table->sh_offset);
	
	for (index = 0; index<no_of_sections; ++index) {
		if (7 == strlen(section_header_string_table_pointer+sectionTable[index].sh_name)) {
			if (0 == strncmp(".strtab" , section_header_string_table_pointer+sectionTable[index].sh_name , 6)) {
			return current_section->sh_offset;
			}
		}
		current_section = (Elf32_Shdr*)((unsigned int)current_section + (header->e_shentsize));
	}
	return -1;
}  

int getSymbolTableOffset (Elf32_Ehdr* header , void* map_start)  {
	Elf32_Shdr* sectionTable = NULL;
	Elf32_Shdr* current_section = NULL;
	int no_of_sections = 0;
	int index = 0;
	
	no_of_sections = header->e_shnum;
	
	sectionTable = (Elf32_Shdr*)((unsigned int)header + (header->e_shoff));
	
	current_section = (Elf32_Shdr*)sectionTable;
	
	Elf32_Shdr* section_header_string_table = &sectionTable[header->e_shstrndx];
	
	void* section_header_string_table_pointer = map_start + section_header_string_table->sh_offset;
	
	for (index = 0; index<no_of_sections; ++index) {
		if (7 == strlen(section_header_string_table_pointer+sectionTable[index].sh_name)) {
			if (0 == strncmp(".symtab" , section_header_string_table_pointer+sectionTable[index].sh_name , 6)) {
			return current_section->sh_offset;
			}
		}
		current_section = (Elf32_Shdr*)((unsigned int)current_section + (header->e_shentsize));
	}
	return -1;
}


int getNumberOfSymbols (Elf32_Ehdr* header , void* map_start)  {

	Elf32_Shdr* sectionTable = NULL;
	Elf32_Shdr* current_section = NULL;
	int no_of_sections = 0;
	int index = 0;
	int sizeOfSymbolEntry = 16;
	
	no_of_sections = header->e_shnum;
	
	sectionTable = (Elf32_Shdr*)((unsigned int)header + (header->e_shoff));
	
	current_section = (Elf32_Shdr*)sectionTable;
	
	Elf32_Shdr* section_header_string_table = &sectionTable[header->e_shstrndx];
	
	void* section_header_string_table_pointer = map_start + section_header_string_table->sh_offset;
	
	for (index = 0; index<no_of_sections; ++index) {
		if (7 == strlen(section_header_string_table_pointer+sectionTable[index].sh_name)) {
			if (0 == strncmp(".symtab" , section_header_string_table_pointer+sectionTable[index].sh_name , 6)) {
			return (((int)(current_section->sh_size))/sizeOfSymbolEntry);
			}
		}
		current_section = (Elf32_Shdr*)((unsigned int)current_section + (header->e_shentsize));
	}
	return -1;
}

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
	/*Elf32_Shdr* current_section = NULL;
	int no_of_sections = 0;*/
	int index = 0;
	int SymbolTableOffset = -1;
	int NumberOfSymbols = -1;
	int sizeOfSymbolEntry = sizeof(Elf32_Sym);
	
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
	printf("\nmap_start = %x\n" , (unsigned int)map_start);
	header = (Elf32_Ehdr*) map_start;
	printf("\nheader = %x\n" , (unsigned int)header);
if (1 == notElf(header)) {
	perror("\nnot an ELF file, terminating...\n");
	_exit(0);
}

	/*no_of_sections = header->e_shnum;
	printf("\nNumber of sections: %d\n" , no_of_sections);
	*/
	
	sectionTable = (Elf32_Shdr*)((unsigned int)header + (header->e_shoff));
	/*
	printf("\nthe section table starts at %x\n" , (unsigned int)sectionTable);
	
	current_section = (Elf32_Shdr*)sectionTable;
	*/
	/*
	printf("\n%x\n" , current_section->sh_addr);
	*/
	
	Elf32_Shdr* section_header_string_table = &sectionTable[header->e_shstrndx];
	char* section_header_string_table_pointer = map_start + section_header_string_table->sh_offset;
	
	char *symbol_string_table_pointer = map_start +  getStrTableOffset(header , map_start);
	
	/*
	Elf32_Shdr* sh_strtab = &shdr[header->e_shstrndx];
	const char* const sh_strtab_p = p + sh_strtab->sh_offset;
	*/

	
	SymbolTableOffset = getSymbolTableOffset(header , map_start);
	if (SymbolTableOffset == -1) {
		perror("\ncouldn't get SymbolTableOffset. Terminating....\n\n");
		_exit(0);
	}
	NumberOfSymbols = getNumberOfSymbols(header , map_start);
	
	printf("\nsymbol table offset: %x\n\n" , SymbolTableOffset);
	printf("\nnumber of symbols: %d\n\n" , NumberOfSymbols);
	
	Elf32_Sym* symbol_table = (Elf32_Sym*)((unsigned int)header + SymbolTableOffset);
	printf("\n\naddress of symbol table: %x\n\n" , (unsigned int)symbol_table);
	
	Elf32_Sym* current_symbol = (Elf32_Sym*)symbol_table;
	
/* task specification: [index] value section_index section_name symbol_name */
	printf("%-6s%-18s%-18s%-18s%-18s \n \n" , " [index]" , " value" , "section_index" , "section_name" , "symbol_name");
	for (index = 0 ; index < NumberOfSymbols ; ++index) {
		printf("[%3d:] " , index);/* index */
		printf("%16x  " , current_symbol->st_value);/* value */

		printf("%16d  " , current_symbol->st_shndx);/* section index */
		if (current_symbol->st_shndx != 0xfff1 && current_symbol->st_shndx !=0 )
			printf("%-15s",section_header_string_table_pointer + sectionTable[current_symbol->st_shndx].sh_name);
		else if(current_symbol->st_shndx  == 0xfff1)
			printf("%-15s","ABS");
		else
			printf("%-15s","UND");

		

		printf("%-15s",(char*)(symbol_string_table_pointer + current_symbol->st_name)); /* section name */

		
		/*printf("%-15s",(char*)(section_header_string_table_pointer + ((Elf32_Sym*)(symbol_table[index])).st_name)); symbol name */
		/*printf("%10x" , current_section->sh_size);*/ /* symbol name */
		printf("\n");
		current_symbol = (Elf32_Sym*)((unsigned int)current_symbol + sizeOfSymbolEntry);
		
	}
	
	
	return 1;
}