#!/bin/bash

#STEP 1

#./run.sh
#ls -l *.dat
echo "----------Creating Files----------"
cat /dev/random | head -c 100000 > src_1.dat
cat /dev/random | head -c 200000 > src_2.dat
cat /dev/random | head -c 300000 > src_3.dat
cat /dev/random | head -c 400000 > src_4.dat
cat /dev/random | head -c 500000 > src_5.dat
cat /dev/random | head -c 600000 > src_6.dat
cat /dev/random | head -c 700000 > src_7.dat
cat /dev/random | head -c 800000 > src_8.dat
cat /dev/random | head -c 900000 > src_9.dat
cat /dev/random | head -c 1000000 > src_10.dat

# Compile the C program
echo "Compiling the C program..."
gcc -o file_copy 1.c -pthread

# Run the program with the provided arguments
echo "Running the program..."
./file_copy src_1.dat dst_1.dat src_2.dat dst_2.dat src_3.dat dst_3.dat src_4.dat dst_4.dat src_5.dat dst_5.dat src_6.dat dst_6.dat src_7.dat dst_7.dat src_8.dat dst_8.dat src_9.dat dst_9.dat src_10.dat dst_10.dat



# STEP 2