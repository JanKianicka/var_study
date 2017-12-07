package java_study;

public class OperatorTest {

   public static void main(String args[]) {
      int a, b;
      a = 10;
      b = (a == 1) ? 20: 30;
      System.out.println( "Value of b is : " +  b );

      b = (a == 10) ? 20: 30;
      System.out.println( "Value of b is : " + b );
      
      OperatorTest name = new OperatorTest();
      boolean result = name instanceof OperatorTest;
      System.out.println("Name is instance of OperatorTest:" + result);
      
      
   }
}