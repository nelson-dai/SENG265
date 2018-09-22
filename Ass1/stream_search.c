#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

ssize_t getline(char **, size_t *, FILE *);

int main(int argc,char *argv[]){
    
    
    if(argc != 2){
        fprintf(stderr,"Usage: ./stream_search <word list file>\n");
        exit(-1);
    }
    
    FILE * searchfor;
    searchfor = fopen(argv[1],"r");
    
    if( searchfor == NULL){
        fprintf(stderr,"Error: Unable to open word list\n");
        exit(-1);
    }
    
    ssize_t sizeSource;
    size_t lengthSource;
    char *linesearch = NULL;
    
	int array[1000];
        int counter = 0;
	int flag =0;
    
    while ((sizeSource = getline(&linesearch,&lengthSource,searchfor)) != -1) {
        
        if (linesearch[sizeSource - 1] == '\n')
            linesearch[sizeSource - 1] = '\0';
        
        ssize_t sizeTarget;
        size_t lengthTarget;
       char *lineFrom = NULL;
        rewind(stdin);

	int lineNumber = 0;
	if(sizeSource != 1){
        while ((sizeTarget = getline(&lineFrom,&lengthTarget,stdin)) != -1) {
		flag = 0;
            if (lineFrom[sizeTarget - 1] == '\n')
                lineFrom[sizeTarget - 1] = '\0';
            if(strstr(lineFrom,linesearch) != NULL){
		
                for(int i =0;i<counter;i++){

			if(lineNumber == array[i]){
			  flag = 1;  
			}
		}
			if(flag == 0){
			 printf("%s\n",lineFrom);
			 array[counter] = lineNumber;
			
			 counter++;
			}else{
			}
               
               
            }
		lineNumber++;
        }
}
    }
    
    fclose(searchfor);
    return 0;
}
