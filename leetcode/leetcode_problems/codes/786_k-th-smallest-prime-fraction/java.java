import java.util.*;

class Solution {
    public int[] kthSmallestPrimeFraction(int[] arr, int k) {
        PriorityQueue<double[]> heap = new PriorityQueue<>((a, b) -> Double.compare(a[0], b[0]));
        int n = arr.length;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                heap.offer(new double[]{arr[i] * 1.0 / arr[j], arr[i], arr[j]});
            }
        }
        
        for (int i = 0; i < k - 1; i++) {
            heap.poll();
        }
        
        double[] result = heap.poll();
        return new int[]{(int)result[1], (int)result[2]};
    }
}
