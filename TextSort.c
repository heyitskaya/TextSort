#include <stdio.h>
#include <stdlib.h>
void getFileContent(const char *name, char *arr[][100]);
int main(int argc, char *argv[]){
	char stringArr[][100];
	char *fileName= &(*argv[1]);
	printf("%s", fileName);	
	getFileContent(fileName, &stringArr);
}

void getFileContent(const char *name, char *arr[][100]){
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
		arr[currIndex]=line;
		currIndex++;
		fprintf(stdout,"%s",line);
	}
	fclose(fp);	
}