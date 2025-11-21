# Name: Benjamin Banh
# Date: 9/24/2
# Title: Lab 1: Unix/Linux Commands and Basic Shell Programming
# Description:  Write a shell program to compute the area and the perimeter of a circle with the value of the
                # circle's radius taken as input from the user. Check the value to make sure it is a strictly positive number.
                # Calculation of the area and the perimeter must be performed as functions.

#Copy of step1.sh
#!/bin/sh
echo Executing $0

response="Yes"
while [ "$response" != "No" ]; do
    echo "Enter radius of the circle: "
    read radius
    if [ $radius -lt 0 ]
    then
        echo "Invalid value"
        exit 1
    fi

    # Calculate perimeter using bc for floating-point math
    perimeter=$(echo "scale=2; 2 * 3.14 * $radius" | bc)
    area=$(echo "scale=2; 3.14 * $radius * $radius" | bc)
    echo "The perimeter of the circle is $perimeter"
    echo "The area of the circle is $area"
    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done
