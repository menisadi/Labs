#include <stdio.h>
#include <stdlib.h>

void printTest(char* buffer,long length) {
	int i = 0;
	while (i < length) { 
		int j = i;
		int len = 0;
		int place = 1;
		while (i < j + 4) {
			len = len + place*(buffer[i]);
			place = place * 100;
			i++;
		}
		j = i;
		char signat[len];
		while (i < j+len) {
			/*printf("%02hhX ", buffer[i]);*/
			signat[i-j] = buffer[i];
			i++;
		}
		j = i;
		printf("\n");
		char name[100];
		while (buffer[i] != 0) {
			/*printf("%C", buffer[i]);*/
			name[i-j] = buffer[i];
			i++;
		}
		name[i-j] = '\0';
		i++;

		int k;
		printf("Virus name: %s\n", name);
		printf("Virus size: %i ", len);
		printf("\n");
		printf("Signature: \n");
		for (k = 0; k < len; k++) {
			printf("%02hhX ", signat[k]);
		}
		printf("\n");

		printf("\n");
	} 
	printf("\n");
}

int main(int argc, char **argv) {
	FILE *signs = fopen("signatures", "r");
	fseek(signs,0,SEEK_SET);
	fseek(signs,0,SEEK_END);
	long size = ftell(signs);
	fseek(signs,0,SEEK_SET);
	char *signBuff= malloc(size + 1);
	fread(signBuff,size,1,signs);
	printTest(signBuff,size);
	free(signBuff);
	fclose(signs);
	return 0;
}