package java_study;

public class EmployeeTest {

   public static void main(String args[]) {
      /* Create two objects using constructor */
      Employee empOne = new Employee("James Smith");
      Employee empTwo = new Employee("Mary Anne");

      // Invoking methods for each object created
      empOne.empAge(26);
      empOne.empDesignation("Senior Software Engineer");
      empOne.empSalary(1000);
      empOne.printEmployee();

      empTwo.empAge(21);
      empTwo.empDesignation("Software Engineer");
      empTwo.empSalary(500);
      empTwo.printEmployee();
   }
}

/* Literals */
class Literals {
	byte a = 68;
	char b = 'A';
	/* Prefix 0 is used to indicate octal, and prefix 0x indicates hexadecimal */
	int decimal = 100;
	int octal = 0144;
	int hexa =  0x64;
	String text = "\"This is in quotes\"";
	
}


