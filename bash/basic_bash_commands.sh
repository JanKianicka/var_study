#!/bin/sh

echo "For loop"
for f in `ls -1`; 
do 
    echo "File: $f";
done

# reading of values from stdout
echo "What is your name?"
# read PERSON - we skip this for now
echo "Hello, $PERSON"

# Variables
NAME="Zara Ali"
VAR1=15245
readonly VAR2="Longer string"

echo "NAME: $NAME"
echo "VAR2: $VAR2"
# VAR2="New string" - not allowed
# ./bash/basic_bash_commands.sh: line 21: VAR2: readonly variable

# removing the variable from the list
# only for non-readonly variables
unset VAR1

# Special variables in shell
# pid of the current shell
echo "PID of the current shell: $$"
echo "File name of the current script: $0"
echo "Number of arguments: $#"
echo "Arguments: $*"