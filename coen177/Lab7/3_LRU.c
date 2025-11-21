#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    int pageno;
    int locality; // For LRU 
} ref_page;


int find(int value, ref_page cache[], int size);
int get_LRU(ref_page cache[], int size);

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
        // printf("%d ",page_num);
		// Page Replacement Implementation Goes Here 
        if (cache_size < C_SIZE){ //space in queue
            int index = find(page_num, cache, C_SIZE);
            if (index == -1){ //add if not queue if not found
                cache[curr_ptr].pageno = page_num;
                cache[curr_ptr].locality = time;
                totalFaults ++;
                curr_ptr = (curr_ptr+1) % C_SIZE;
                cache_size++;
                printf("%d\n",page_num);
                // printf("Fault");
            }
            else{
                //hit
                cache[index].locality = time;

            }
        }
        else {
            int index = find(page_num, cache, C_SIZE);
            if(index != -1){ // found
                cache[index].locality = time;

            }
            else{
                int index = get_LRU(cache, C_SIZE);

                cache[index].pageno = page_num;
                cache[index].locality = time;
                totalFaults ++;
                printf("%d\n",page_num);
                // printf("Fault");
            }

        }
        // printf("\n");
        time ++; // for total number of page requests and LRU
    }
    // printf("%d Total Requests\n", time);
    // printf("%d Total Page Faults\n", totalFaults);
    return 0;

}

//finds the index of the specified value from cache array else -1
int find(int value, ref_page cache[], int size){
    for (int i = 0; i < size; i++){
        if(cache[i].pageno == value) {
            return i;
        }
    }
    return -1;
}

//finds the index of the LRU value 
int get_LRU(ref_page cache[], int size){
    int min = cache[0].locality;
    int index = 0; 
    for (int i = 0; i < size; i++){
        if(cache[i].locality < min) {
            min = cache[i].locality;
            index = i;
        }
    }
    return index;
}