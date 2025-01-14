package java_study;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class StringTest {

	public static void main(String[] args) {
		String greeting = "Hello world!";
		char[] helloArray = { 'h', 'e', 'l', 'l', 'o', '.' };
		String helloString = new String(helloArray);
		System.out.println(helloString);
		// accessor method
		int len = greeting.length();
	    System.out.println( "String Length is : " + len );

	    String fs;
	    fs = String.format("The value of the float variable is " +
	                       "%f, while the value of the integer " +
	                       "variable is %d, and the string " +
	                       "is %s", 0.025, 7, "StringVar");
	    System.out.println(fs);

	    String Str = new String("Welcome to Tutorialspoint.com");
	    System.out.println("Hashcode for Str :" + Str.hashCode() );
	    
	    // md5 hash code 
//		byte[] bytesOfMessage = null;
//		try {
//			bytesOfMessage = Str.getBytes();
//			System.out.println(bytesOfMessage.toString());
//		} catch (UnsupportedEncodingException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}

	    MessageDigest md = null;
		try {
			md = MessageDigest.getInstance("MD5");
			
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 
		try {
			String Str2 = new String(Str.getBytes("UTF-8"));
			System.out.println("Returned Value " + Str2);
			Str2 = new String(Str.getBytes("ISO-8859-1"));
			System.out.println("Returned Value " + Str2);
		} catch (UnsupportedEncodingException e) {
			System.out.println("Unsupported character set");
		}
		
		/* This is very strange, this md5 hash is always the same even though I change the input string. */
		/* There must be something puzzling here. */
	    byte[] thedigest = md.digest(Str.getBytes());
	    System.out.println(thedigest.toString());
	    
		StringBufferTest.run();
	}

}



/*
 * String class methods:
 * 
1 	char charAt(int index)
Returns the character at the specified index.

2 	int compareTo(Object o)

Compares this String to another Object.
3 	int compareTo(String anotherString)

Compares two strings lexicographically.
4 	int compareToIgnoreCase(String str)

Compares two strings lexicographically, ignoring case differences.
5 	String concat(String str)

Concatenates the specified string to the end of this string.
6 	boolean contentEquals(StringBuffer sb)

Returns true if and only if this String represents the same sequence of characters as the specified StringBuffer.
7 	static String copyValueOf(char[] data)

Returns a String that represents the character sequence in the array specified.
8 	static String copyValueOf(char[] data, int offset, int count)

Returns a String that represents the character sequence in the array specified.
9 	boolean endsWith(String suffix)

Tests if this string ends with the specified suffix.
10 	boolean equals(Object anObject)

Compares this string to the specified object.
11 	boolean equalsIgnoreCase(String anotherString)

Compares this String to another String, ignoring case considerations.
12 	byte getBytes()

Encodes this String into a sequence of bytes using the platform's default charset, storing the result into a new byte array.
13 	byte[] getBytes(String charsetName)

Encodes this String into a sequence of bytes using the named charset, storing the result into a new byte array.
14 	void getChars(int srcBegin, int srcEnd, char[] dst, int dstBegin)

Copies characters from this string into the destination character array.
15 	int hashCode()

Returns a hash code for this string.
16 	int indexOf(int ch)

Returns the index within this string of the first occurrence of the specified character.
17 	int indexOf(int ch, int fromIndex)

Returns the index within this string of the first occurrence of the specified character, starting the search at the specified index.
18 	int indexOf(String str)

Returns the index within this string of the first occurrence of the specified substring.
19 	int indexOf(String str, int fromIndex)

Returns the index within this string of the first occurrence of the specified substring, starting at the specified index.
20 	String intern()

Returns a canonical representation for the string object.
21 	int lastIndexOf(int ch)

Returns the index within this string of the last occurrence of the specified character.
22 	int lastIndexOf(int ch, int fromIndex)

Returns the index within this string of the last occurrence of the specified character, searching backward starting at the specified index.
23 	int lastIndexOf(String str)

Returns the index within this string of the rightmost occurrence of the specified substring.
24 	int lastIndexOf(String str, int fromIndex)

Returns the index within this string of the last occurrence of the specified substring, searching backward starting at the specified index.
25 	int length()

Returns the length of this string.
26 	boolean matches(String regex)

Tells whether or not this string matches the given regular expression.
27 	boolean regionMatches(boolean ignoreCase, int toffset, String other, int ooffset, int len)

Tests if two string regions are equal.
28 	boolean regionMatches(int toffset, String other, int ooffset, int len)

Tests if two string regions are equal.
29 	String replace(char oldChar, char newChar)

Returns a new string resulting from replacing all occurrences of oldChar in this string with newChar.
30 	String replaceAll(String regex, String replacement

Replaces each substring of this string that matches the given regular expression with the given replacement.
31 	String replaceFirst(String regex, String replacement)

Replaces the first substring of this string that matches the given regular expression with the given replacement.
32 	String[] split(String regex)

Splits this string around matches of the given regular expression.
33 	String[] split(String regex, int limit)

Splits this string around matches of the given regular expression.
34 	boolean startsWith(String prefix)

Tests if this string starts with the specified prefix.
35 	boolean startsWith(String prefix, int toffset)

Tests if this string starts with the specified prefix beginning a specified index.
36 	CharSequence subSequence(int beginIndex, int endIndex)

Returns a new character sequence that is a subsequence of this sequence.
37 	String substring(int beginIndex)

Returns a new string that is a substring of this string.
38 	String substring(int beginIndex, int endIndex)

Returns a new string that is a substring of this string.
39 	char[] toCharArray()

Converts this string to a new character array.
40 	String toLowerCase()

Converts all of the characters in this String to lower case using the rules of the default locale.
41 	String toLowerCase(Locale locale)

Converts all of the characters in this String to lower case using the rules of the given Locale.
42 	String toString()

This object (which is already a string!) is itself returned.
43 	String toUpperCase()

Converts all of the characters in this String to upper case using the rules of the default locale.
44 	String toUpperCase(Locale locale)

Converts all of the characters in this String to upper case using the rules of the given Locale.
45 	String trim()

Returns a copy of the string, with leading and trailing whitespace omitted.
46 	static String valueOf(primitive data type x)

Returns the string representation of the passed data type argument.
 * 
 * 
 */

// StringBuffer and StringBuilder are feasible for String manipulations.
class StringBufferTest {

	protected static void run() {
		StringBuffer sBuffer = new StringBuffer("test");
		sBuffer.append(" String Buffer");
		System.out.println(sBuffer);
	}
}


/*
 * Most important StringBuffer methods:
public StringBuffer append(String s)
Updates the value of the object that invoked the method. The method takes boolean, char, int, long, Strings, etc.

2 	public StringBuffer reverse()
The method reverses the value of the StringBuffer object that invoked the method.

3 	public delete(int start, int end)
Deletes the string starting from the start index until the end index.

4 	public insert(int offset, int i)
This method inserts a string s at the position mentioned by the offset.

5 	replace(int start, int end, String str)
This method replaces the characters in a substring of this StringBuffer with characters in the specified String.

*
*/



