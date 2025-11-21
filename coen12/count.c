//Benjamin Banh
//4/6/23
/**
 * Implement an application to read words from a text file.
 * Program should display the total number of words in the file
 */

#include <stdio.h>
#define MAX_WORD_LENGTH 30
int main(int argc, char *argv[])
{
    //variables
    FILE* fp;
    char c[MAX_WORD_LENGTH];
    int word_count = 0;
    
    
    if (argc != 2){
        printf ("The name of the file is missing!\n");
        return 1;  

    }

    //change fName later
    fp = fopen(argv[1], "r");
 
    if (fp==NULL) {
        printf("Error opening the file \n");
        return 0;
    }
 
    while(fscanf(fp,"%s",c) == 1){
        word_count++;
    }
 
    // Closing the file
    fclose(fp);
    printf("%d Total Words", word_count);
}

