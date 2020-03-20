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

# Special Parameters $* and $@
echo "Processing arguments using \$*:" 
for TOKEN in $*
do
   echo $TOKEN
done

echo "Processing arguments using \$@:"
for TOKEN in $@
do
   echo $TOKEN
done
# error invocation
touch /root/xxx
echo "Exist status of the last command: $?"

echo "Shell Arrays" 
NAME01="Zara"
NAME02="Qadir"
NAME03="Mahnaz"
NAME04="Ayan"
NAME05="Daisy"
# can be stored as
NAME[0]="Zara"
NAME[1]="Qadir"
NAME[2]="Mahnaz"
NAME[3]="Ayan"
NAME[4]="Daisy"
echo "First element of the array: $NAME"
echo "First element of the array using {}: ${NAME[0]} "
# elements can be accessed via [*] or [@]
for name in ${NAME[*]}
do
    echo $name
done

NAME2=('value1' 'value2' 'value3')
# in csh - % set -A array_name value1 value2 ... valuen
echo "All elements of NAME2 at once: ${NAME2[@]}"

# concatenating and splitting arrays-string
# adding comma to the string
NAME2_STRING=$(IFS=, ; echo "${NAME2[*]}")
echo "NAME2_STRING: $NAME2_STRING"
# bach to array
NAME2_NEWARR=(${NAME2_STRING//,/ })
echo "Back to array NAME2_NEWARR: ${NAME2_NEWARR[@]}"

# Hash map (dictionary) in bash
declare -A animals
animals=( ["moo"]="cow" ["woof"]="dog")
# setting new value
animals['caa']='cat'
# getting value
echo "${animals[moo]}"
# getting all values
echo "All values of hash-map: ${animals[@]}"
# getting all keys
echo "All keys of hash-map: ${!animals[@]}"

# Shell does not support nested arrays - arrays of arrays!

# Bourne shell basic operators
# originally we have to use awk or expr 
# there must be spaces: 2 + 2 (not 2+2)
# enclosed between ‘ ‘, called the backtick.
val=`expr 2 + 2`
echo "Total value : $val"

asign_a=23
asign_b=$asign_a
echo [ $asign_a == $asign_b ]
if [ $asign_a == $asign_b ]
then 
   echo "asign_a equals to asign_b"
fi

# spaces around them. For example, [ $a <= $b ] is correct whereas, [$a <= $b] is incorrect.
if [ $asign_a -eq $asign_b ]
then 
    echo "asign_a equals to asign_b using -eq"
fi

# boolean operators
if [ !false ]
then
    echo "!false is true"
    if [ $asign_a -gt 20 -o $asign_b -lt 20 ]
    then
	echo "OR evaluation of $asign_a -gt 20 -o $asign_b -lt 20"
	if [ $asign_a -gt 20 -a $asign_b -ge 23 ]
	then
	    echo "AND evaluation of $asign_a -gt 20 -a $asign_b -ge 23"
	fi
    fi
fi

string_a='abc'
string_b='efg'

if [ $string_a != $string_b ]
then
    echo "String equlity: $string_a = $string_b not true."
fi

# The same with negation outside the condition
if ! [[ $string_a = $string_b ]]
then
    echo "String equlity: ! [[\$string_a = \$string_b]] not true."
fi

# Testing of files
if [ -b /dev/sda ]; then echo "/dev/sda is block special file"; fi
if [ -c /dev/null ]; then echo "/dev/null is character special file"; fi

# Interesting if..elif..else chain
a=10
b=20
if [ $a == $b ]
then
   echo "a is equal to b"
elif [ $a -gt $b ]
then
   echo "a is greater than b"
elif [ $a -lt $b ]
then
   echo "a is less than b"
else
   echo "None of the condition met"
fi

# case..asac 
FRUIT="kiwi"
case "$FRUIT" in
   "apple") echo "Apple pie is quite tasty." 
   ;;
   "banana") echo "I like banana nut bread." 
   ;;
   "kiwi") echo "New Zealand is famous for kiwi." 
   ;;
esac

# Usage for parsing command line options
# option="${1}" 
# case ${option} in 
#   -f) FILE="${2}" 
#      echo "File name is $FILE"
#      ;; 
#   -d) DIR="${2}" 
#      echo "Dir name is $DIR"
#      ;; 
#   *)  
#      echo "`basename ${0}`:usage: [-f file] | [-d directory]" 
#      exit 1 # Command to come out of the program with status 1
#      ;; 
# esac 


# Nested while loop
a=0
while [ "$a" -lt 10 ]    # this is loop1
do
   b="$a"
   while [ "$b" -ge 0 ]  # this is loop2
   do
      echo -n "$b "
      b=`expr $b - 1`
   done
   echo
   a=`expr $a + 1`
done

# for loop - space separated list in the input
for var in 0 1 2 3 4 5 6 7 8 9
do
   echo $var
done

for FILE in $HOME/*
do
   echo $FILE
done