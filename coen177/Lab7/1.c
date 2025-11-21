#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    int numRequests = atoi(argv[2]); // Number of lines in txt file 
    int maxPageNumber = atoi(argv[3]); // Range of Numbers in txt file 0-num
    
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<numRequests; i++){
        sprintf(buffer, "%d\n", rand()%(maxPageNumber-5)+5);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}