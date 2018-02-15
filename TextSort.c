#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
void sortFile(char *arr[10]);
void sortFileWithIndex(char *arr[10]);
int compareStrings(const void *elem1, const void *elem2);

//global variable
//int index; 
int numWords = 2; 
int main(int argc, char *argv[]){
	int numLines=10;
	char *stringArr[numLines];
	char *fileName;
	char *flag;
	
	printf("argc %i\n", argc);
	if(argc==0){
		printf("Error");
	}

	else if (argc == 3) {
		fileName = &(*argv[1]);
		flag = &(*argv[2]); 
		
		if (strlen(flag) == 2) { 
			//adding code to read flag, just need to change the number to int from char properly
			//char *end; 
			//index = (int) strtol(flag[1], (char **)NULL, 10); 
			//printf("Flag is %d\n", index);
		}
		else {
			printf("Error: bad command line paramter");
			exit(1); 
		} 			 
	}

	else if(argc==2){
		fileName = &(*argv[1]);
	}

	else{
	//	numWord=*argv[1];
		fileName = &(*argv[2]);
	}
		
	getFileContent(fileName, stringArr);
	//sortFile(stringArr);
	//testing sort with index
	//int x;
	//x = compareStringsWithIndex(&stringArr[1], &stringArr[2]);
	//printf("the number is %d\n", x);
	
		
	if(numWords!=0){
		printf("testing sort file with index ");
		sortFileWithIndex(stringArr);
	}
	else{
		sortFile(stringArr);
	} 
	//sortFileWithIndex(stringArr);
	for(int i=0;i<5;i++){
		printf("-----------\n");
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
	
int compareStringsWithIndex(const void *elem1, const void *elem2){
	char **strptr1=(char **) elem1;
	char **strptr2=(char **) elem2;
	/**deference to get strings**/
	char *str1 = *strptr1;
	char *str2 = *strptr2;

	char *copy1 = malloc(strlen(str1)+1); 
	char *copy2 = malloc(strlen(str2)+1);
	strcpy(copy1, str1); 
	strcpy(copy2, str2); 
	/**split on space**/
	const char s[2] = " "; 
	char *token1;  
	char *token2; 
	
	token1 = strtok(copy1, s); 
	/**get nth tokens**/ 	
	int i = 0; 
	while (token1!=NULL && i < (numWords-1)) { 
		token1=strtok(NULL, s); 
		i++; 
	} 	
	char *word1 = token1; 
	printf("word1 ");
	printf(word1);	
	token2 = strtok(copy2, s); 
	int j = 0; 
	while (token2!=NULL && j < (numWords-1)) {
		token2 = strtok(NULL, s);
		j++; 
	} 
	
	char *word2 = token2;  
	printf("word 2 %s", word2);	
	/**compare nth tokens**/
	int diff; 
	diff = strcmp(word1, word2); 
	return diff; 
}

void sortFileWithIndex(char *arr[10]){
	qsort(arr, 5, sizeof(char *), compareStringsWithIndex);
}
void sortFile(char *arr[10]) {
	qsort(arr, 5, sizeof(char *), compareStrings); 
}

