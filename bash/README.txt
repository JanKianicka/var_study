# Learning from https://www.tutorialspoint.com/unix/shell_scripting.htm

Importnat notes here from the tutorial's point:
Two basic types of shell:    
    Bourne shell − If you are using a Bourne-type shell, the $
    character is the default prompt.
    Subcategories:
	Bourne shell (sh), Korn shell (ksh), Bourne Again shell (bash), 
	POSIX shell (sh)

    C shell − If you are using a C-type shell, the % character is the
    default prompt.
    	    Subcategories: C shell (csh), TENEX/TOPS C shell (tcsh)

Variable names:
- upper case, must not contain number,!*-
There are three types of variables: local, environmental, shell

Command line arguments - try:
$ ./basic_bash_commands.sh arg1 arg2 arg3 arg4

The $? variable represents the exit status of the previous command.

Shell Arrays:

bash operators:
Bourne shell didn't originally have any mechanism to perform simple arithmetic operations but it uses external programs, either awk or expr.
`expr $a + $b` will give 30
`expr $a - $b` will give -10
`expr $a \* $b` will give 200
`expr $b / $a` will give 2 
`expr $b % $a` will give 0 - Modulus
a = $b would assign value of b into a
[ $a == $b ] would return false.
[ $a != $b ] would return true.

spaces around them, for example [ $a == $b ] is correct whereas, [$a==$b] is incorrect.

Numerical relational operators:
-eq - equals:     [ $a -eq $b ] is not true.
-ne - not equals: [ $a -ne $b ] is true.
-gt - greater:    [ $a -gt $b ] is not true.
-lt - less:       [ $a -lt $b ] is true.
-ge - greater or equal:  [ $a -ge $b ] is not true.
-le - less or equal:     [ $a -le $b ] is true.
spaces around them. For example, [ $a <= $b ] is correct whereas, [$a <= $b] is incorrect.

Boolean operators:
! - logical negation: [ ! false ] is true.
-o - logical OR: [ $a -lt 20 -o $b -gt 100 ] is true.
-a - logical AND: [ $a -lt 20 -a $b -gt 100 ] is false.

String operators:
= - equality:      [ $a = $b ] is not true.
!= - non equliaty: [ $a != $b ] is true.
-z - size is zero: [ -z $a ] is not true.
-n - size is non-zero: [ -n $a ] is not false.
str - str is not the empty string: [ $a ] is not false.

