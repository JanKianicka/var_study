package java_study;

class ThreadDemoSynchronized extends Thread {
   private Thread t;
   private String threadName;
   PrintDemo  PD;

   ThreadDemoSynchronized( String name,  PrintDemo pd) {
      threadName = name;
      PD = pd;
   }
   
   public void run() {
      synchronized(PD) {
         PD.printCount();
      }
      System.out.println("Thread " +  threadName + " exiting.");
   }

   public void start () {
      System.out.println("Starting " +  threadName );
      if (t == null) {
         t = new Thread (this, threadName);
         t.start ();
      }
   }
}


public class TestThreadSynchronized {

   public static void main(String args[]) {
      PrintDemo PD = new PrintDemo();

      ThreadDemoSynchronized T1 = new ThreadDemoSynchronized( "Thread - 1 ", PD );
      ThreadDemoSynchronized T2 = new ThreadDemoSynchronized( "Thread - 2 ", PD );

      T1.start();
      T2.start();

      // wait for threads to end
      try {
         T1.join();
         T2.join();
      } catch ( Exception e) {
         System.out.println("Interrupted");
      }
   }
}

// This is the result
/*
Starting Thread - 1 
Starting Thread - 2 
Counter   ---   5
Counter   ---   4
Counter   ---   3
Counter   ---   2
Counter   ---   1
Thread Thread - 1  exiting.
Counter   ---   5
Counter   ---   4
Counter   ---   3
Counter   ---   2
Counter   ---   1
Thread Thread - 2  exiting. 

 */
