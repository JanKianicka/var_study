package java_study;

class PrintDemo {
	public void printCount() {
		try {
			for (int i = 5; i > 0; i--) {
				System.out.println("Counter   ---   " + i);
				Thread.sleep(10);
			}
		} catch (Exception e) {
			System.out.println("Thread  interrupted.");
		}
	}
}

class ThreadDemoUnsynchronized extends Thread {
	private Thread t;
	private String threadName;
	PrintDemo PD;

	ThreadDemoUnsynchronized(String name, PrintDemo pd) {
		threadName = name;
		PD = pd;
	}

	public void run() {
		PD.printCount();
		System.out.println("Thread " + threadName + " exiting.");
	}

	public void start() {
		System.out.println("Starting " + threadName);
		if (t == null) {
			t = new Thread(this, threadName);
			t.start();
		}
	}
}

public class TestThreadUnsynchronized {
	public static void main(String args[]) {

		PrintDemo PD = new PrintDemo();

		ThreadDemoUnsynchronized T1 = new ThreadDemoUnsynchronized("Thread - 1 ", PD);
		ThreadDemoUnsynchronized T2 = new ThreadDemoUnsynchronized("Thread - 2 ", PD);

		T1.start();
		T2.start();

		// wait for threads to end
		try {
			T1.join();
			T2.join();
		} catch (Exception e) {
			System.out.println("Interrupted");
		}
	}
}

// This is the result
/* Starting Thread - 1 
Starting Thread - 2 
Counter   ---   5
Counter   ---   5
Counter   ---   4
Counter   ---   4
Counter   ---   3
Counter   ---   3
Counter   ---   2
Counter   ---   2
Counter   ---   1
Counter   ---   1
Thread Thread - 1  exiting.
Thread Thread - 2  exiting. */
