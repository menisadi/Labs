#include <stdio.h>
#include <stdlib.h>

void PrintHex(char* buffer,long length) {
	int i;
	for (i=0; i < length; i++) {
		printf("%02hhX ", buffer[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	FILE *binary = fopen(argv[1], "r");
	fseek(binary,0,SEEK_END);
	long size = ftell(binary);
	printf("%lu\n", size);
	fseek(binary,0,SEEK_SET);
	char *fbuffer = malloc(size + 1);
	fread(fbuffer,size,1,binary);
	/* fbuffer[size] = '\0'; */
	PrintHex(fbuffer,size);
	fclose(binary);
	return 0;
}