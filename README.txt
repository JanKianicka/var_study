# This is the study of Java from this tutorial:
# https://www.tutorialspoint.com/java

1. We are now here:
https://www.tutorialspoint.com/java/java_basic_syntax.htm

Running hello world from command line:
> cd /home/local/kianicka/repositories/var_study/java_study/src
> export CLASSPATH="/home/local/kianicka/repositories/var_study/java_study/src"
> javac java_study/MyFirstJavaProgram.java
> java java_study/MyFirstJavaProgram
Hello World

Crucial realities in Java:
- identifiers (names)
- modifiers
- variables
- arrays
- enums

- reserved words:
abstract 	assert 	boolean 	break
byte 	case 	catch 	char
class 	const 	continue 	default
do 	double 	else 	enum
extends 	final 	finally 	float
for 	goto 	if 	implements
import 	instanceof 	int 	interface
long 	native 	new 	package
private 	protected 	public 	return
short 	static 	strictfp 	super
switch 	synchronized 	this 	throw
throws 	transient 	try 	void
volatile 	while


- inheritance - from a single class
- interface - 

Object-oriented concept:
    Polymorphism
    Inheritance
    Encapsulation
    Abstraction
    Classes
    Objects
    Instance
    Method
    Message Parsing

1. Local variables
2. Instance variables
3. Class variables

The main rule of constructors is that they should have the same name
as the class.
Creating objects:
Three options: 
1. Declaration
2. Instantiation
3. Initialization

There can be only one public class per source file.
A source file can have multiple non-public classes.

Java packages:
Import and package statements will imply to all the classes present in
the source file. It is not possible to declare different import and/or
package statements to different classes in the source file.


Data types:
1. Primitive data types
2. Derived object data types

byte (8-bit, from -128 to 127)
short (16-bit signed, from -32,768 to 32,767)
int   (32-bit signed, from - 2,147,483,648 to 2,147,483,647)
long  (64-bit signed, from -9,223,372,036,854,775,808(-2^63) to 
       9,223,372,036,854,775,807 (inclusive)(2^63 -1))
float (32-bit IEEE 754 floating point)
double (64-bit IEEE 754 floating point)
boolean (1bit)
char  (single 16-bit Unicode character, from '\u0000' to  '\uffff')

Special string characters:
\n 	Newline (0x0a)
\r 	Carriage return (0x0d)
\f 	Formfeed (0x0c)
\b 	Backspace (0x08)
\s 	Space (0x20)
\t 	tab
\" 	Double quote
\' 	Single quote
\\ 	backslash
\ddd 	Octal character (ddd)
\uxxxx 	Hexadecimal UNICODE character (xxxx)

Local variables are internally stored in the stack.
Instance variables - in class but outside methods.  Instance variables
have default values. For numbers, the default value is 0, for Booleans
it is false, and for object references it is null.

Statick variables - There would only be one copy of each class
variable per class, regardless of how many objects are created from
it. Static variables are rarely used other than being declared as
constants.

Access modifiers:

    Visible to the package, the default. No modifiers are needed.
    Visible to the class only (private).
    Visible to the world (public).
    Visible to the package and all subclasses (protected).

Non-access modifiers:

    The static modifier for creating class methods and variables.
    The final modifier for finalizing the implementations of classes,
    methods, and variables.
    The abstract modifier for creating abstract classes and methods.
    The synchronized and volatile modifiers, which are used for threads.


Ended in https://www.tutorialspoint.com/java/java_basic_operators.htm
