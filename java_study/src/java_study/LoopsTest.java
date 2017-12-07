package java_study;

public class LoopsTest {

	public static void main(String args[]) {
		whileLoopTest();
		forLoopTest();
		doWhileLoopTest();
		enhancedLoopTest();
		decisionMakeingTest();
	}

	private static void whileLoopTest() {
		int x = 10;

		while (x < 20) {
			System.out.print("value of x : " + x);
			x++;
			System.out.print("\n");
		}
	}
	
	private static void forLoopTest(){
		for(int x = 10; x < 20; x = x + 1) {
	         System.out.print("value of x : " + x );
	         System.out.print("\n");
	      }
	}
	
	private static void doWhileLoopTest(){
		int x = 10;

		do {
			++x;
			if( x == 15 ){
				continue;
			}
			System.out.print("value of x : " + x);
			System.out.print("\n");

			if( x == 19 ){
				break;
			}

		} while (x < 20);
	}
	
	private static void enhancedLoopTest() {
		int[] numbers = { 10, 20, 30, 40, 50 };

		for (int x : numbers) {
			System.out.print(x);
			System.out.print(",");
		}
		System.out.print("\n");
		String[] names = { "James", "Larry", "Tom", "Lacy" };

		for (String name : names) {
			System.out.print(name);
			System.out.print(",");
		}
	}
	
	private static void decisionMakeingTest() {
		DecisionMaking decTestObject = new DecisionMaking();
		decTestObject.elseIfTest();
		decTestObject.switchTest();
	}
	
}


class DecisionMaking {
	
	protected void elseIfTest() {
		int x = 30;

		if (x == 10) {
			System.out.print("Value of X is 10");
		} else if (x == 20) {
			System.out.print("Value of X is 20");
		} else if (x == 30) {
			System.out.print("Value of X is 30");
		} else {
			System.out.print("This is else statement");
		}
	}
	
	protected void switchTest() {
		// char grade = args[0].charAt(0);
		char grade = 'C';

		switch (grade) {
		case 'A':
			System.out.println("Excellent!");
			break;
		case 'B':
		case 'C':
			System.out.println("Well done");
			break;
		case 'D':
			System.out.println("You passed");
		case 'F':
			System.out.println("Better try again");
			break;
		default:
			System.out.println("Invalid grade");
		}
		System.out.println("Your grade is " + grade);
	}
}