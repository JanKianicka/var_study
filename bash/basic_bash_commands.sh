#!/bin/sh

echo "For loop"
for f in `ls -1`; 
do 
    echo "File: $f";
done

# reading of values from stdout
echo "What is your name?"
read PERSON
echo "Hello, $PERSON"