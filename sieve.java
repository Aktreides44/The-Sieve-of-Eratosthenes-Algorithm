import java.util.Arrays;

public class sieve {
	// Counting prime func
    public static long countPrimes(int N) {

        byte[] flags = new byte[N + 1];
        Arrays.fill(flags, (byte) 1);

        // 0 and 1 are not prime numbers, so set them to 0
        flags[0] = 0;
        if (N >= 1) flags[1] = 0;

        int limit = (int) Math.sqrt(N);
        for (int p = 2; p <= limit; p++) {
            if (flags[p] == 1) {
                for (int k = p * p; k <= N; k += p) {
                    flags[k] = 0;
                }
            }
        }

        long count = 0;
        for (int i = 0; i <= N; i++) {
            if (flags[i] == 1) {
                count++;
            }
        }

        return count;
    }

    // Medican function
    private static double getMedian(double[] array) {
        double[] sorted = array.clone();
        Arrays.sort(sorted);
        int len = sorted.length;
        if (len % 2 == 0) {
            return (sorted[len / 2 - 1] + sorted[len / 2]) / 2.0;
        } else {
            return sorted[len / 2];
        }
    }

    public static void runBenchmark(int N, int warmupRuns, int measuredRuns) {
	//Warmup 5 times
        for (int i = 0; i < warmupRuns; i++) {
            countPrimes(N);
        }

	//Run 10 times
        double[] timingsMs = new double[measuredRuns];
        long lastCount = 0;

        for (int i = 0; i < measuredRuns; i++) {
            long t0 = System.nanoTime();
            lastCount = countPrimes(N);
            long t1 = System.nanoTime();
            timingsMs[i] = (t1 - t0) / 1e6; // Convert nanoseconds to milliseconds
        }

        // Print the final run times 
        System.out.printf("N = %d | pi(N) = %d%n", N, lastCount);
        System.out.print("  Runs (ms): [");
        for (int i = 0; i < measuredRuns; i++) {
            System.out.printf("%.3f%s", timingsMs[i], (i < measuredRuns - 1) ? ", " : "");
        }
        System.out.println("]");
        System.out.printf("  Median: %.3f ms%n%n", getMedian(timingsMs));
    }

    public static void main(String[] args) {
        System.out.println("--- Task 2: Java Performance Measurement ---");
        int[] testNs = {100000, 1000000, 10000000}; // N = 10^5, 10^6, 10^7
        for (int N : testNs) {
            runBenchmark(N, 5, 10);
        }
    }
}
