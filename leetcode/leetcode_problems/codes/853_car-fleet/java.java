import java.util.*;

class Solution {
    public int carFleet(int target, int[] position, int[] speed) {
        int n = position.length;
        int[][] cars = new int[n][2];
        for (int i = 0; i < n; i++) {
            cars[i] = new int[]{position[i], speed[i]};
        }
        Arrays.sort(cars, (a, b) -> a[0] - b[0]);
        
        double[] times = new double[n];
        for (int i = 0; i < n; i++) {
            times[i] = (double)(target - cars[i][0]) / cars[i][1];
        }
        
        int result = 0;
        double cur = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (times[i] > cur) {
                result++;
                cur = times[i];
            }
        }
        return result;
    }
}
