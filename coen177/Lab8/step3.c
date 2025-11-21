#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   
    
    FILE *fp;
    fp = fopen(argv[1], "rb");
    int s = atoi(argv[2]);
    char buffer[s];

    while (fread(buffer, 1, sizeof(buffer), fp)){
    
    }
    fclose(fp);
}
