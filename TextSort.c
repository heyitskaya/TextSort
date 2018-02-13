#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
//int compareStrings(const void **str1, const void **str2);
void sortFile(char *arr[10][100]);
int main(int argc, char *argv[]){
	printf("in main");
	int numLines=10;
	char *stringArr[numLines];	
	char *fileName= &(*argv[1]);
	printf("%s", fileName);	
	printf("before fileContent");
	getFileContent(fileName, stringArr);
	printf("index 3 %s",	(char**)stringArr[3]);
	char str1[] = "Hello"; 
	char str2[] = "World";
	printf("above compareStrings");
	//compareStrings(&str1, &str2); 
}

void getFileContent(const char *name, char *arr[10]){
	FILE *fp;
	char line[256];
	fp=fopen(name, "r");
	int currIndex=0;
	if(fp==NULL){
		exit(EXIT_FAILURE);
	}
	printf("before while");
	while(fgets(line,sizeof line, fp)!=NULL){
		printf("in while loop");
		arr[currIndex]=malloc(strlen(line)+1); //250 chars
		strcpy(arr[currIndex],line);
		currIndex++;
	}
	printf("before close");
	fclose(fp);	
//	printf("At end of fileContent");
}

int compareStrings (const void *elem1, const void *elem2) {

//	printf("Here");
	/**cast to actual type**/
	char **strptr1;// = malloc(sizeof(char **));
	strptr1 = (char **) elem1; 
	char **strptr2;// = malloc(sizeof(char **));
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

