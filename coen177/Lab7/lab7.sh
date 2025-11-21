#!/bin/bash
make;
echo "-------------STEP 1-------------"
#   ./1 BUFFER_SIZE NUM_PRODUCED VAL_RANGE
./1 5 100 100
echo "Produced testInput.txt of 100"
echo "-------------STEP 2-------------"
# cat testInput.txt | ./2 5
echo "-------------STEP 3-------------"

echo "----------FIFO----------"
cat testInput.txt | ./3_FIFO 10
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./3_LRU 10
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./3_2C 10
echo "----------End Second Chance----------"
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./3_FIFO 10 | wc -l
cat accesses.txt | ./3_FIFO 50 | wc -l
cat accesses.txt | ./3_FIFO 100 | wc -l
cat accesses.txt | ./3_FIFO 250 | wc -l
cat accesses.txt | ./3_FIFO 500 | wc -l
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./3_LRU 10 | wc -l
cat accesses.txt | ./3_LRU 50 | wc -l
cat accesses.txt | ./3_LRU 100 | wc -l
cat accesses.txt | ./3_LRU 250 | wc -l
cat accesses.txt | ./3_LRU 500 | wc -l
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./3_2C 10 | wc -l
cat accesses.txt | ./3_2C 50 | wc -l
cat accesses.txt | ./3_2C 100 | wc -l
cat accesses.txt | ./3_2C 250 | wc -l
cat accesses.txt | ./3_2C 500 | wc -l
echo
make clean;
echo