#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
void sortFile(char *arr[10]);
int compareStrings(const void *elem1, const void *elem2);
int main(int argc, char *argv[]){
	printf("in main");
	int numLines=10;
	char *stringArr[numLines];	
	char *fileName= &(*argv[1]);
	getFileContent(fileName, stringArr);
	for(int i=0;i<5;i++){
		printf("index %s",stringArr[i]); //char * is a string
	}
	
	char str1[] = "Hello"; 
	char str2[] = "World";
//	int comp=compareStrings(&str1, &str2);
//	printf("diff is %i", comp);
	sortFile(stringArr);
	for(int i=0;i<5;i++){
		printf(stringArr[i]);
	}
}

void getFileContent(const char *name, char *arr[10]){
	FILE *fp;
	char line[256];
	fp=fopen(name, "r");
	int currIndex=0;
	if(fp==NULL){
		exit(EXIT_FAILURE);
	}
	while(fgets(line,sizeof line, fp)!=NULL){
		arr[currIndex]=malloc(strlen(line)+1); //250 chars
		strcpy(arr[currIndex],line);
		currIndex++;
	}
	fclose(fp);	
}

int compareStrings (const void *elem1, const void *elem2) {
	/**cast to actual type**/
	char **strptr1;
	strptr1 = (char **) elem1; 
	char **strptr2;
	strptr2 = (char **) elem2; 
	/**dereference to get strings**/	
	char *str1 = *strptr1; 
	char *str2 = *strptr2;	
	int diff;	
	diff = strcmp (str1, str2); 
	printf("%d", diff); 
	return diff; 
}
	

void sortFile(char *arr[10]) {
	qsort(arr, 5, sizeof(char *), compareStrings); 
}

