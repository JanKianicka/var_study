#!/bin/sh

#trap 'catch' ERR
trap 'catch $? $LINENO' ERR

catch () {
    echo "An error occured"
    echo "Error $1 on line $2"
    exit 1
}

echo "Start"
simple
touch does/not/exist
echo "Successful end"

# Trap handles just return status of the function,
# not the code of the function itself.
simple() {
  echo "Hi from simple()!"
  badcommand
}


