package java_study;

public class CharacterTest {

	public static void main(String[] args) {
		char ch = 'a';
		// Unicode for uppercase Greek omega character
		char uniChar = '\u039A'; 
		// an array of chars
		char[] charArray = { 'a', 'b', 'c', 'd', 'e' };
		System.out.println(uniChar);
		
		// Here following primitive char 'a'
		// is boxed into the Character object ch
		Character ch_obj = 'a';
		/* Here has to be used Character class, not the object */
		System.out.println(Character.isLowerCase(ch_obj));
	}
}



/*
 * Methods of Character class:
 * 
 * 
1 	isLetter()
Determines whether the specified char value is a letter.

2 	isDigit()
Determines whether the specified char value is a digit.

3 	isWhitespace()
Determines whether the specified char value is white space.

4 	isUpperCase()
Determines whether the specified char value is uppercase.

5 	isLowerCase()
Determines whether the specified char value is lowercase.

6 	toUpperCase()
Returns the uppercase form of the specified char value.

7 	toLowerCase()
Returns the lowercase form of the specified char value.

8 	toString()
Returns a String object representing the specified character value that is, a one-character string.

 * 
 * */


/* 
 * Java escape sequences:
 * 
 * 

\t 	Inserts a tab in the text at this point.
\b 	Inserts a backspace in the text at this point.
\n 	Inserts a newline in the text at this point.
\r 	Inserts a carriage return in the text at this point.
\f 	Inserts a form feed in the text at this point.
\' 	Inserts a single quote character in the text at this point.
\" 	Inserts a double quote character in the text at this point.
\\ 	Inserts a backslash character in the text at this point.

 * 
 * */
 