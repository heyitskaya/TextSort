#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
void sortFile(char *arr[10]);
int compareStrings(const void *elem1, const void *elem2);
int main(int argc, char *argv[]){
	int numLines=10;
	char *stringArr[numLines];
	printf("numWord is %i\n", argc);	
	int numWord=0;
	char *fileName;//= &(*argv[1]);
	if(argc==0){
		printf("Error");
	}
	else if(argc==2){
		fileName = &(*argv[1]);
		//getFileContent(fileName, stringArr);
	}
	else{
		numWord=*argv[1];
		fileName = &(*argv[2]);
	}
		
	getFileContent(fileName, stringArr);
	sortFile(stringArr);
	for(int i=0;i<5;i++){
		printf(stringArr[i]);
	}
	//testing sort with index
	
	/**
	int x;
	x = compareStringsWithIndex(&stringArr[1], &stringArr[2], 4);
	printf("%d", x);
	**/
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
	
int compareStringsWithIndex(const void *elem1, const void *elem2, int index){
	char **strptr1=(char **) elem1;
	char **strptr2=(char **) elem2;
	/**deference to get strings**/
	char *str1 = *strptr1;
	char *str2 = *strptr2;
	

	/**split on space**/
	const char s[2] = " "; 
	char *token1;  
	char *token2; 
	
	token1 = strtok(str1, s); 
	/**get nth tokens**/ 	
	int i = 0; 
	while (token1!=NULL && i < (index-1)) { 
		token1=strtok(NULL, s); 
		i++; 
	} 	
	char *word1 = token1; 
	
	token2 = strtok(str2, s); 
	int j = 0; 
	while (token2!=NULL && j < (index-1)) {
		token2 = strtok(NULL, s);
		j++; 
	} 
	
	char *word2 = token2;  
	/**compare nth tokens**/
	int diff; 
	diff = strcmp(word1, word2); 
	return diff; 
	
}


void sortFile(char *arr[10]) {
	qsort(arr, 5, sizeof(char *), compareStrings); 
}

