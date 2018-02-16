#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getFileContent(const char *name, char *arr[10]);
void sortFile(char *arr[10]);
void sortFileWithIndex(char *arr[10]);
int compareStrings(const void *elem1, const void *elem2);
int getNumLines(const char *name); 
int numLines;
int numWords;

/**Read command line arguments, make sure they are valid, store file content, sort file based on parameters**/ 
int main(int argc, char *argv[]){
	char *fileName;
	char *flag;
	
	if(argc==0){
		fprintf(stderr, "Error: Bad command line parameters\n");
	}
	else if (argc == 3) {
		fileName = &(*argv[2]);
		numLines=getNumLines(fileName);	
		flag = &(*argv[1]);
		
		char *ptr;
		int asc1=(int)flag[1];

		//check that flag is at least 2 characters long, begins with a dash, and the second character is a digit 
		if(flag[0]!='-' || strlen(flag)<2 || asc1<49 || asc1>57){
			fprintf(stderr,"Error: Bad command line parameter\n");
			exit(1);
		} 
   		//get index to sort by	
		numWords=((int)strtol(flag,&ptr,10))*(-1);	
	}
	
	//if no flag is given, sort by first word
	else if(argc==2){
		fileName = &(*argv[1]);
		numLines=getNumLines(fileName);	
		
		FILE *fp=fopen(fileName,"r");
		//if the only argument is not a file, print error
		if(fp==NULL){
			fprintf(stderr,"Error: Bad command line parameter\n");
			exit(1);
		}
		fclose(fp); 
	}

	else{
		fprintf(stderr,"Error: Bad command line parameter\n");
		exit(1); 

	}
	//allocate size of array before getFileContent
	char *stringArr[numLines];		
	getFileContent(fileName, stringArr);
	for(int i=0;i<numLines;i++){
		int len=strlen(stringArr[i]);
		if(len>128){
			fprintf(stderr,"Error: Line too long\n");
			exit(1);
		}
		
	}
		
	//if flag is specified	
	if(numWords!=0){
		sortFileWithIndex(stringArr);
	}
	else{ 
		sortFile(stringArr);
	}

	//print sorted file and free memory 
	for(int i=0;i<numLines;i++){
		printf("%s", stringArr[i]);
	}
	for(int j=0;j<numLines;j++){
		free(stringArr[j]);
	}
	return 0;
}

/** Get number of lines in the file**/
int getNumLines(const char *name){
	int n=0;
	FILE *fp;
	char line[256];
	fp=fopen(name,"r");
	if(fp==NULL){
		fprintf(stderr, "Error: Cannot open file\n");
		exit(1);
	}
	while(fgets(line,sizeof line, fp)!=NULL) {
		n++;
	}
	return n;
}

/**Stores file content in an array**/
void getFileContent(const char *name, char *arr[numLines]){
	 
	FILE *fp;
	char line[256];
	fp=fopen(name, "r");
	int currIndex=0;
	if(fp==NULL){
		fprintf(stderr,"Error: Cannot open file %s", name);
		exit(1);
	}
	while(fgets(line,sizeof line, fp)!=NULL){
		arr[currIndex]=malloc(strlen(line)+1); 
		strcpy(arr[currIndex],line);
		currIndex++;
	}
	fclose(fp);	
}
/**Get word count of a sentence and returns it**/
int wordCount(char * s){
	int count =0;	
	for(int i=0;s[i]!='\0';i++){
		if(s[i] == ' '){
			count++;
		}
	}	
	return count+1;
}
/**Comparator called when no flag is specified, sorts on first word**/
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
	return diff; 
}

/**Comparator called when flag is specified, sorts on word given by flag**/
int compareStringsWithIndex(const void *elem1, const void *elem2){
	char **strptr1=(char **) elem1;
	char **strptr2=(char **) elem2;
	/**deference to get strings**/
	char *str1 = *strptr1;
	char *str2 = *strptr2;
	int wc1=wordCount(str1);
	int wc2=wordCount(str2);
	
	char *copy1 = malloc(strlen(str1)+1); 
	char *copy2 = malloc(strlen(str2)+1);
	strcpy(copy1, str1);
	strcpy(copy2, str2); 
	/**split on space**/
	const char s[2] = " "; 
	char *token1;  
	char *token2; 
	char *word1;  
	/**get nth tokens**/ 	
	int i = 0;
	/**if the flag given is within bounds of the length of the string**/
	if (wc1 > numWords-1) {
		token1 = strtok(copy1, s);
		while (token1!=NULL && i < (numWords-1)) { 
			token1=strtok(NULL, s); 
			i++; 
		} 
		
		word1 = token1;
	}
	/**Get last word and sort by last word**/
	else {
		char *p=strrchr(copy1, ' ');
		if(p!=NULL){
			word1 = p+1;  
		}

	}
 
	int j = 0;
	char *word2;
	if(wc2>numWords-1){ 
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
	diff = strcmp(word1, word2); 
	free(copy1); 
	free(copy2);
	return diff; 
}

/**Call this sort when flag is specified**/
void sortFileWithIndex(char *arr[numLines]){
	qsort(arr, numLines, sizeof(char *), compareStringsWithIndex);
}
/**Call this sort when flag is not specified**/
void sortFile(char *arr[numLines]) {
	qsort(arr, numLines, sizeof(char *), compareStrings); 
}

