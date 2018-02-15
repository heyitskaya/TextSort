#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
void sortFile(char *arr[10]);
void sortFileWithIndex(char *arr[10]);
int compareStrings(const void *elem1, const void *elem2);
int numLines;
//global variable
//int index; 
int numLines;
int numWords; 
int main(int argc, char *argv[]){
	//int numLines=getNumLines;
	//char *stringArr[numLines];
	char *fileName;
	char *flag;
	
	printf("argc %i\n", argc);
	printf( argv[2]);
	if(argc==0){
		printf("Error");
	}

	else if (argc == 3) {
		fileName = &(*argv[1]);
		numLines=getNumLines(fileName);	
		flag = &(*argv[2]); 
		
		//adding code to read flag, just need to change the number to int from char properly 
		char *ptr;
   			
		numWords=((int)strtol(flag,&ptr,10))*(-1);	
		printf("num is %d", numWords);
		
		 			 
	}

	else if(argc==2){
		fileName = &(*argv[1]);
	}

	else{
	//	numWord=*argv[1];
		fileName = &(*argv[2]);
	}
//allocate size of array before getFileContent
	char *stringArr[numLines];		
	getFileContent(fileName, stringArr);
	
		
	if(numWords!=0){
	//	printf("testing sort file with index ");
		sortFileWithIndex(stringArr);
	}
	else{
		sortFile(stringArr);
	} 
	//sortFileWithIndex(stringArr);
	for(int i=0;i<numLines;i++){
		printf("-----------\n");
		printf(stringArr[i]);
	}
	//free(stringArr);
	for(int j=0;j<numLines;j++){
		free(stringArr[j]);
	}
}
int getNumLines(const char *name){
	int n=0;
	FILE *fp;
	char line[256];
	fp=fopen(name,"r");
	if(fp==NULL){
		exit(EXIT_FAILURE);
	}
	while(fgets(line,sizeof line, fp)!=NULL) {
		n++;
	}
	printf("numLines is %d", n);
	return n;
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

int wordCount(char * s){
int count =0;	
for(int i=0;s[i]!='\0';i++){
		if(s[i] == ' '){
			count++;
		}
	}	
return count+1;
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
	int wc1=wordCount(str1);
	printf("wc1 %d", wc1);
	int wc2=wordCount(str2);
	
	char *copy1 = malloc(strlen(str1)+1); 
	char *copy2 = malloc(strlen(str2)+1);
	strcpy(copy1, str1);
	printf("after allocation copy1 %s\n", copy1); 
	strcpy(copy2, str2); 
	/**split on space**/
	const char s[2] = " "; 
	char *token1;  
	char *token2; 
	char *word1;  
	/**get nth tokens**/ 	
	int i = 0;
	
	if (wc1 > numWords-1) {
		token1 = strtok(copy1, s);
	while (token1!=NULL && i < (numWords-1)) { 
		token1=strtok(NULL, s); 
		i++; 
	} 
		
	word1 = token1;
	}
	else {
		char *p=strrchr(copy1, ' ');
		if(p!=NULL){
			word1 = p+1;  
		}

	}
 

	int j = 0;
	char *word2;
	if(wc2>numWords-1){ //MIGHT FUCK UP LATER pls check
		token2 = strtok(copy2, s);
 
		while (token2!=NULL && j < (numWords-1)) {
			token2 = strtok(NULL, s);
			j++;
			}
		word2=token2;	
	}
	else{	
		char *q = strrchr(copy2, ' '); 
		if (q != NULL ) {
		word2 = q+1;
		} 
	}
	/**compare nth tokens**/
	int diff;
	printf("word1 %s\n", word1);
	printf("word2 %s\n", word2);
	diff = strcmp(word1, word2); //don't forget to add back
	free(copy1); 
	free(copy2);
	return diff; 
}

void sortFileWithIndex(char *arr[10]){
	qsort(arr, 5, sizeof(char *), compareStringsWithIndex);
}
void sortFile(char *arr[10]) {
	qsort(arr, 5, sizeof(char *), compareStrings); 
}

