import java.util.Arrays;

public class PerfTest {
	

    public static void main(String[] args) {
    	long startTime = System.currentTimeMillis();
    	
    	double[] array = new double[100000000];
    	double j = 0.0;
    	for (int i = 0; i < array.length; i++) {
    		array[i] = j;
    		j = j + 1.0;
    	}
    	
        for (double element : array) {
        	Math.sin(element);
        }
        long estimatedTime = System.currentTimeMillis() - startTime;
        System.out.println("Duration - sin: " + estimatedTime/1000.0);
        
        // string manupulation yet
        System.out.println("String maniplation");
        String result;
        for (double element : array) {
        	result = String.format("%.3f", element);
        }
        estimatedTime = System.currentTimeMillis() - startTime;
        System.out.println("Duration overall: " + estimatedTime/1000.0);
        System.out.println("Exited");
    }
}
