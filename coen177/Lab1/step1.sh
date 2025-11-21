# Name: Benjamin Banh
# Date: 9/24/2
# Title: Lab 1: Unix/Linux Commands and Basic Shell Programming
# Description:  This lab is designed to introduce you to the basics of the Linux technical
#               environment, including tools, commands, and shell scripts.

#Sample shell program for the Lab assignment
#!/bin/sh
echo Executing $0   #Prints "Executing ./[filename]"
echo $(/bin/ls | wc -l) files   #Prints the number of files on the current directory
wc -l $(/bin/ls) #Prints the number of lines per file and the corresponding file

#Prints environment variables
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH   
echo "PWD="$PWD
echo "\$\$"=$$ 

# Verifies the user
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "bbanh" ] #use your username instead of salagtash
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
exit 1
fi

#Calculates the area of a rectangle
response="Yes"
while [ $response != "No" ]
do
    echo "Enter height of rectangle: "
    read height
    echo "Enter width of rectangle: "
    read width
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area"
    echo "Would you like to repeat for another rectangle [Yes/No]?"
    read response
done