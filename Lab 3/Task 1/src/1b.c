#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus virus;
 
struct virus {
        int length;
        char *signature;
        char *name;
        virus *next;
};

void list_print(virus *virus_list) {
	if (virus_list!= 0) {
		list_print(virus_list->next);
		printf("Virus name: %s\n", virus_list->name);
		printf("Virus size: %i\n", virus_list->length);
		int k;
		for (k = 0; k < strlen(virus_list->signature); k++) {
				printf("%02hhX ", virus_list->signature[k]);
	 	}
		printf("\n\n");
	}
}
   
virus *list_append(virus *virus_list, virus *data) {
	data->next = virus_list;
	return data;
}

void list_free(virus *virus_list) {
	if (virus_list != 0)
		list_free(virus_list->next);
	free(virus_list);
}

virus* createList(char* buffer,long length) {
	virus* list = 0;
	int i = 0;
	while (i < length) { 
		virus* newVirus = (virus*)malloc(sizeof(virus));
		int j = i;
		int len = 0;
		int place = 1;
		while (i < j + 4) {
			len = len + place*(buffer[i]);
			place = place * 100;
			i++;
		}
		j = i;
		char* signat = (char*) malloc(len);
		while (i < j+len) {
			signat[i-j] = buffer[i];
			i++;
		}
		j = i;
		printf("\n");
		char* vname = (char*) malloc(100);
		while (buffer[i] != 0) {
			vname[i-j] = buffer[i];
			i++;
		}
		vname[i-j] = '\0';
		i++;

		newVirus->name = vname;
		newVirus->length = len;
		newVirus->signature = signat;
		newVirus->next = 0;

		list = list_append(list,newVirus);
	} 
	return list;
}

int main(int argc, char **argv) {
	FILE *signs = fopen("signatures", "r");
	fseek(signs,0,SEEK_SET);
	fseek(signs,0,SEEK_END);
	long size = ftell(signs);
	fseek(signs,0,SEEK_SET);
	char *signBuff= malloc(size + 1);
	fread(signBuff,size,1,signs);
	virus* myList = createList(signBuff,size);
	list_print(myList);
	list_free(myList);
	free(signBuff);
	fclose(signs);
	return 0;
}