#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int lives;
} ref_page;


int find(int value, ref_page cache[], int size);
int updateLives(int value, ref_page cache[], int size);
int replace(int value, ref_page cache[], int size, int curr_ptr);

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
        cache[i].lives = 0;
    }

    int val;
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        // printf("%d",page_num);
		// Page Replacement Implementation Goes Here 
        
        int idx = find(page_num, cache, C_SIZE);

        if (idx != -1) {
            // PAGE HIT
            cache[idx].lives = 1;
        } 
        else {
            // PAGE FAULT
            totalFaults++;
            printf("%d\n",page_num);

            if (cache_size < C_SIZE) {
                // Cache not full — insert directly
                cache[curr_ptr].pageno = page_num;
                cache[curr_ptr].lives = 1;
                curr_ptr = (curr_ptr + 1) % C_SIZE;
                cache_size++;
                
            } 
            else {
                // Cache full — Clock replacement
                curr_ptr = replace(page_num, cache, C_SIZE, curr_ptr);
            }
        }
        // printf("\n");
        time ++; // for total number of page requests and LRU
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

int updateLives(int value, ref_page cache[], int size){
    int index = find(value, cache, size);
    if (index != -1){
        cache[index].lives = 1;
    }
}


int replace(int value, ref_page cache[], int size, int curr_ptr){
    while (1) {
        if (cache[curr_ptr].lives != 1) {
            // Replace with new page
            cache[curr_ptr].pageno = value;
            // Return updated pointer
            return (curr_ptr + 1) % size;
            printf("%d\n",value);
        }
        // Mark it 'false' as it got one chance
        // and will be replaced next time unless accessed again
        cache[curr_ptr].lives = 0;
        // Pointer is updated in round robin manner
        curr_ptr = (curr_ptr + 1) % size;
    }
}
