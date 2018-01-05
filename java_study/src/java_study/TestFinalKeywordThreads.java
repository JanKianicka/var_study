package java_study;

public class TestFinalKeywordThreads {
    public static void main(String[] args) {
        // Create the resultset containing the result
        ResultSet resultSet = new ResultSet(10);
        Thread[] threads = new Thread[resultSet.getSize()];

        // Create threads
        for (int i = 0; i < resultSet.getSize(); i++) {
            threads[i] = new Thread(new TestTask(
                    resultSet.createResultSetter(i),i));
        }

        // Start threads
        for (int i = 0; i < resultSet.getSize(); i++) {
            threads[i].start();
        }

        // Wait until threads complete
        for (int i = 0; i < resultSet.getSize(); i++) {
            try {
                threads[i].join();
            } catch (InterruptedException exception) {
                // ??!
            }
        }

        // Print the result
        for (int i = 0; i < resultSet.getSize(); i++) {
            System.out.println(resultSet.getResult(i));
        }
    }

    /**
     * Interface used to set the result
     */
    public static interface ResultSetter {
        public void setResult(int result);
    }

    /**
     * Container class for results
     */
    public static class ResultSet {
        private final int[] results;

        public ResultSet(int size) {
            results = new int[size];
        }

        public int getSize() {
            return results.length;
        }

        public ResultSetter createResultSetter(final int position) {
            return new ResultSetter() {
                public void setResult(int result) {
                    ResultSet.this.setResult(position, result);
                }
            };
        }

        public synchronized int getResult(int position) {
            return results[position];
        }

        public synchronized void setResult(int position, int result) {
            results[position] = result;
        }
    }

    /**
     * A task executed by a thread
     */
    public static class TestTask implements Runnable {
        private ResultSetter resultSetter;
        private int value;

        public TestTask(ResultSetter resultSetter, int inValue) {
            this.resultSetter = resultSetter;
            this.value = inValue;
        }

        @Override
        public void run() {
            resultSetter.setResult(this.value);
        }
    }
}