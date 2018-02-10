#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[][100]);
//int compareStrings(const void **str1, const void **str2);
void sortFile(char *arr[10][100]);
int main(int argc, char *argv[]){
	printf("in main");
	char stringArr[10][100];
	char *fileName= &(*argv[1]);
	printf("%s", fileName);	
	getFileContent(fileName, &stringArr);
	printf("at index 1");
//	printf("%s", stringArr[1][100]);

	char str1[100] = "Hello"; 
	char str2[100] = "World";
//	compareStrings(&str1, &str2); 
}

void getFileContent(const char *name, char *arr[10][100]){
	FILE *fp;
	int c;
	size_t len=0;
	ssize_t read;
	char line[256];
	fp=fopen(name, "r");
	int currIndex=0;
	if(fp==NULL){
		exit(EXIT_FAILURE);
	}
	while(fgets(line,sizeof line, fp)!=NULL){
		arr[currIndex][100]=line;
		currIndex++;
		fprintf(stdout,"%s",line);
	}
	fclose(fp);	
}

int compareStrings (const void *elem1, const void *elem2) {
	printf("%s", "Here");
	/**cast to actual type**/
	char **strptr1 = malloc(sizeof(char **));
	strptr1 = (char **) elem1; 
	char **strptr2 = malloc(sizeof(char **));
	**strptr2 = (char **) elem2; 
	/**dereference to get strings**/	
	char *str1 = *strptr1; 
	char *str2 = *strptr2;	
	int diff;	
	diff = strcmp (str1, str2); 
	printf("%d", diff); 
	return diff; 
}
	

void sortFile(char *arr[10][100]) {
	qsort(*arr, 10, 100, compareStrings); 
}

