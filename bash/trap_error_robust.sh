#!/bin/bash
# From here: https://medium.com/@dirk.avery/the-bash-trap-trap-ce6083f36700

# The solution has three parts:
#    a) set exit-on-error mode (set -e),
#    b)trap the exit signal instead of the error, and
#    c) make sure we ended up in catch based on an error.
#
# Notice that we end up in catch() at the end when the script exits
# even though there was no error. Mind the catch!

set -e

trap 'catch $? $LINENO' EXIT

catch() {
  echo "catching!"
  if [ "$1" != "0" ]; then
    # error handling goes here
    echo "Error $1 occurred on $2"
  fi
  # exit 1 - this should be not here, but the non-zero from the failure is returned
}


simple() {
  badcommand
  echo "Hi from simple()!"
}


simple
echo "After simple call"

# Other Options
#
# Besides the robust and strict solution above, there are a few other
# less charming solutions.
#
# One option is to trap errors at the global level but within a
# function check the return code of every statement and return
# immediately on an error.
# 
# Or, we could keep track of a return code in a variable, based on the
# cumulative success and failure of all the statements, and then
# return that value. This way all statements could execute even if an
# error occurs, but the function would be caught regardless of where
# in the function the error occurred.
#
# Another option is to include traps within your functions. If you
# include enough traps, you can make sure that every statement’s
# error’s are trapped.
#
