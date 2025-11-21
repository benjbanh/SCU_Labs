#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    fp = fopen(argv[1], "rb");
    FILE *fp_write = fopen("test.txt", "w+");
    int s = atoi(argv[2]);
    char buffer[s];

    while (fread(buffer, 1, sizeof(buffer), fp)){
        fwrite(buffer, 1, sizeof(buffer), fp_write);
    }
    fclose(fp);
    fclose(fp_write);
}
