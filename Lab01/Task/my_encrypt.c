#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){
	FILE *fin = fopen("input.txt", "r");

	if(fin == NULL){
		perror("File doesn't open porperly!\n");
		exit(0);
	}


	char test;
	while(1){
		test = fgetc(fin);
		if(feof(fin)){
			printf("\nEnd of line\n");
			break;
		}

		
		printf("%c", test);
	}
	
	fclose(fin);
	return 0;
}