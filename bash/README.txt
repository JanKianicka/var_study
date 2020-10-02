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

File operators for bash:
-b file	Checks if file is a block special file; if yes, then the condition becomes true.	[ -b $file ] is false.
-c file	Checks if file is a character special file; if yes, then the condition becomes true.	[ -c $file ] is false.
-d file	Checks if file is a directory; if yes, then the condition becomes true.	       		[ -d $file ] is not true.
-f file	Checks if file is an ordinary file as opposed to a directory or special file; if yes, then the condition becomes true.	[ -f $file ] is true.
-g file	Checks if file has its set group ID (SGID) bit set; if yes, then the condition becomes true.	[ -g $file ] is false.
-k file	Checks if file has its sticky bit set; if yes, then the condition becomes true.	        [ -k $file ] is false.
-p file	Checks if file is a named pipe; if yes, then the condition becomes true.		[ -p $file ] is false.
-t file	Checks if file descriptor is open and associated with a terminal; if yes, then the condition becomes true.	[ -t $file ] is false.
-u file	Checks if file has its Set User ID (SUID) bit set; if yes, then the condition becomes true.	[ -u $file ] is false.
-r file	Checks if file is readable; if yes, then the condition becomes true.	      	      	[ -r $file ] is true.
-w file	Checks if file is writable; if yes, then the condition becomes true.			[ -w $file ] is true.
-x file	Checks if file is executable; if yes, then the condition becomes true.			[ -x $file ] is true.
-s file	Checks if file has size greater than 0; if yes, then condition becomes true.		[ -s $file ] is true.
-e file	Checks if file exists; is true even if file is a directory but exists.			[ -e $file ] is true.

Loops - simple nested, control over loops
Substitions:

\\ backslash
\a alert (BEL)
\b backspace
\c suppress trailing newline
\f form feed
\n new line
\r carriage return
\t horizontal tab
\v vertical tab

You can use the -E option to disable the interpretation of the backslash escapes (default).
You can use the -n option to disable the insertion of a new line.

Substituting variables based on their state:
${var} Substitute the value of var.
${var:-word} If var is null or unset, word is substituted for var. The value of var does not change.
${var:=word} If var is null or unset, var is set to the value of word.
${var:?message} If var is null or unset, message is printed to standard error. This checks that variables are set correctly.
${var:+word} If var is set, word is substituted for var. The value of var does not change.

Metacharcters
Here is a list of most of the shell special characters (also called metacharacters)
* ? [ ] ' " \ $ ; & ( ) | ^ < > new-line space tab

Quoting & Description

Single quote     All special characters between these quotes lose their special meaning.
Double quote     Most special characters between these quotes lose their special meaning with these exceptions −
    $
    `
    \$
    \'
    \"
    \\
Backslash       Any character immediately following the backslash loses its special meaning.
Back quote      Anything in between back quotes would be treated as a command and would be executed.

Ended in IO redirection


Operatos for c-shell:
https://www.tutorialspoint.com/unix/unix-c-shell-operators.htm
(it is bit different subset)

