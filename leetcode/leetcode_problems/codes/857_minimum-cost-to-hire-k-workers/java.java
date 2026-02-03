import java.util.*;

class Solution {
    public double mincostToHireWorkers(int[] quality, int[] wage, int k) {
        int n = quality.length;
        double[][] workers = new double[n][2];
        for (int i = 0; i < n; i++) {
            workers[i] = new double[]{(double)wage[i] / quality[i], quality[i]};
        }
        Arrays.sort(workers, (a, b) -> Double.compare(a[0], b[0]));
        
        PriorityQueue<Double> heap = new PriorityQueue<>(Collections.reverseOrder());
        double sumq = 0;
        double result = Double.MAX_VALUE;
        
        for (double[] worker : workers) {
            double ratio = worker[0];
            double q = worker[1];
            heap.offer(q);
            sumq += q;
            if (heap.size() > k) {
                sumq -= heap.poll();
            }
            if (heap.size() == k) {
                result = Math.min(result, ratio * sumq);
            }
        }
        return result;
    }
}
