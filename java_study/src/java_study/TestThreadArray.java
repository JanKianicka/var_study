package java_study;

class Context {
	public volatile double[] OutListEncaps;
	Context(double[] OutListArg){
		OutListEncaps = OutListArg;
		OutListEncaps[0] = 1.5;
	}
}

class ThreadArray extends Thread {
	private Thread t;
	double[] InList;
	double[] OutList;
	private String threadName;
	Context Con;
	
	ThreadArray(String ThreadNameArg, double[] InListArg, double[] OutListArg, Context ConArg){
		InList = InListArg;
		OutList = OutListArg;
		threadName = ThreadNameArg;
		this.Con = ConArg;
	}
	
	public void run() {
		System.out.println("Value of 2-nd value:"+InList[1]);
		System.out.println("Value of OutListCon, inside threads: " + Con.OutListEncaps[0]);
		OutList[0] = 1.1;
		Con.OutListEncaps[0] = 2.5;
		System.out.println("Value of OutListCon, inside threads 2: " + Con.OutListEncaps[0]);
	}
	
	 public void start () {
	      System.out.println("Starting " +  threadName );
	      if (t == null) {
	         t = new Thread (this, threadName);
	         t.start ();
	      }
	 }

}

class RunnableArray implements Runnable {
	private Thread t;
	private String threadName;
	private double[] OutList;

	RunnableArray(String name, double[] OutListArg) {
		threadName = name;
		System.out.println("Creating " + threadName);
		this.OutList = OutListArg;
		System.out.println("Runnable value:" + this.OutList[0]);
	}

	public void run() {
		this.OutList[0] = 3.5;
		System.out.println("Runnable value:" + this.OutList[0]);
	}

	public void start() {
		System.out.println("Starting " + threadName);
		if (t == null) {
			t = new Thread(this, threadName);
			t.start();
		}
	}
	
	public void join() {
		if (this.t != null) {
			try {
				this.t.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	
}


public class TestThreadArray {

	public static void main(String args[]) {
		double[] InList = { 1.1, 1.2, 1.3, 1.4 };
		double[] OutList = { 0.0, 0.0, 0.0, 0.0 };
		Context Con = new Context(OutList);
		System.out.println("Value of OutList, before threads: " + OutList[0]);
		
		ThreadArray ThreadArray_1 = new ThreadArray("Thread-1", InList, OutList, Con);
		ThreadArray_1.start(); // wait for threads to end
		try {
			ThreadArray_1.join();
		} catch (Exception e) {
			System.out.println("Interrupted");
		}
		System.out.println("Value of OutList, after threads: " + OutList[0]);
		System.out.println("Value of OutList, after threads direct: " + Con.OutListEncaps[0]);
		
		RunnableArray R1 = new RunnableArray( "Thread-1", OutList);
	    R1.start();
	    // Lets try to put here join block as was in C
		try {
			R1.join();
		} catch (Exception e) {
			System.out.println("Interrupted");
		}	    
	    
//		try {
//			Thread.sleep(50);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
	    // So there is issue with synchronization, this means
	    System.out.println("Value of OutList, after runable threads: " + OutList[0]);
	    
// 		So it means call of join has resolved the problem.
	    
	    
		
	}
}
