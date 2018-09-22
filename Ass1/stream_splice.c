#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

ssize_t getline(char **, size_t *, FILE *);
int flag;
char copy[1000];

char * checkword(char *lineFrom,char *deleteword,char firstChar){
   
    for(int i =0;i<=strlen(lineFrom)-strlen(deleteword) ;i++){
        
        int firstCharIndex = 0;
        int counter = 0;
        
        if(firstChar == lineFrom[i]){ //we found the first character
            
            firstCharIndex = i;
            
            for(int j = 0;j<strlen(deleteword);j++){
                if(lineFrom[j + firstCharIndex] == deleteword[j]){
                    
                    counter++;
                }
            }
            
            if(counter == strlen(deleteword)){
                
                flag = 1;
                
                int index =0;
                for (int k = 0; k<strlen(lineFrom); k++) {
                    if(k<firstCharIndex || k >= firstCharIndex+counter){
                         copy[index] = lineFrom[k];
                        index++;
                    }
                }
                
                copy[index] = '\0';
                
               
                return copy;
                
            }
        }
    }
    return lineFrom;
}

int main(int argc,char *argv[]){
    
    
    if(argc != 2){
        fprintf(stderr,"Usage: ./stream_splice <search word>");
        exit(-1);
    }
    
    char * deleteword = argv[1];
    char firstChar = deleteword[0];
    
    ssize_t sizeTarget;
    size_t lengthTarget;
    char *lineFrom = NULL;
    
    
        while ((sizeTarget = getline(&lineFrom,&lengthTarget,stdin)) != -1) {
            
            
            
            if (lineFrom[sizeTarget - 1] == '\n')
                lineFrom[sizeTarget - 1] = '\0';
            
            char * returnword;
             returnword= checkword(lineFrom,deleteword,firstChar);
            while(strstr(returnword,deleteword) != NULL){
                returnword= checkword(returnword,deleteword,firstChar);
            }
            printf("%s\n",returnword);
        }
    
    

    return 0;
}
