package java_study;

import java.util.Arrays;

public class ArrayTest {

	public static void main(String[] args) {
		double[] myList1; // preferred way.
		double myList2[]; // works but not preferred way.
		// declares an array variable, myList3, creates an array of 10 elements
		// of double type and
		// assigns its reference to myList3
		double[] myList3 = new double[10];

		sumFindMaxUsingFor();
		printForeach();
		tryBinarySearch();
	}

	private static void sumFindMaxUsingFor() {
		double[] myList = { 1.9, 2.9, 3.4, 3.5 };

		// Print all the array elements
		for (int i = 0; i < myList.length; i++) {
			System.out.println(myList[i] + " ");
		}

		// Summing all elements
		double total = 0;
		for (int i = 0; i < myList.length; i++) {
			total += myList[i];
		}
		System.out.println("Total is " + total);

		// Finding the largest element
		double max = myList[0];
		for (int i = 1; i < myList.length; i++) {
			if (myList[i] > max)
				max = myList[i];
		}
		System.out.println("Max is " + max);
	}

	private static void printForeach() {
		double[] myList = { 1.9, 2.9, 3.4, 3.5 };

		// Print all the array elements
		for (double element : myList) {
			System.out.println(element);
		}
	}
	
	
	// example of the function which returns reversed 
	// array
	public static int[] reverse(int[] list) {
		int[] result = new int[list.length];

		for (int i = 0, j = result.length - 1; i < list.length; i++, j--) {
			result[j] = list[i];
		}
		return result;
	}
	
	private static void tryBinarySearch(){
		double doubleArr[] = {10.2, 15.1, 2.2, 3.5};
		Arrays.sort(doubleArr);
		double doubleKey = 1.5;
		
		System.out.println(doubleKey + " found at index = "
                +Arrays.binarySearch(doubleArr,doubleKey));
		
		doubleKey = 3.5;
		
		System.out.println(doubleKey + " found at index = "
                +Arrays.binarySearch(doubleArr,doubleKey));
		
		doubleArr[0] = 4.0;
		// this calls implic toString on each object of the array.
		// There is also Arrays.deepToString() for array of arrays.
		System.out.println(Arrays.toString(doubleArr));
		
		Arrays.sort(doubleArr);
		System.out.println(doubleKey + " found at index = "
                +Arrays.binarySearch(doubleArr,doubleKey));
		
	}
	

}

/* 
 * Methods of the java.utils.array class
 * 
 * public static int binarySearch(Object[] a, Object key)
 * Searches the specified array of Object
 * 
 * public static boolean equals(long[] a, long[] a2)
 * Returns true if the two specified arrays of longs are equal to one another.
 * 
 * public static void fill(int[] a, int val)
 * 
 * public static void sort(Object[] a)
 * 
 * */
