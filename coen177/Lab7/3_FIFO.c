#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int find(int value, ref_page cache[], int size);

int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    int cache_size = 0; // current size of cache 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int time = 0;
    int curr_ptr = 0;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
        cache[i].pageno = -1;
    }

    int val;
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        // printf("    %d ",page_num);
        
        val = find(page_num, cache, C_SIZE);
        if (val == -1){ //add if not queue
            if (cache_size < C_SIZE) {
                cache[cache_size].pageno = page_num;
                cache_size++;
            }
            else{
                cache[curr_ptr].pageno = page_num;
                curr_ptr = (curr_ptr+1) % C_SIZE;

            }
            totalFaults ++;
            printf("%d\n",page_num);
        }
        
        // printf("\n");
        time ++; // for total number of page requests
    }
    // printf("%d Total Requests\n", time);
    // printf("%d Total Page Faults\n", totalFaults);
    return 0;



}

//finds the index of the specified value from cache array
int find(int value, ref_page cache[], int size){
    for (int i = 0; i < size; i++){
        if(cache[i].pageno == value) {
            return i;
        }
    }
    return -1;
}
