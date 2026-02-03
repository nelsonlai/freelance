import java.util.*;

class Solution {
    public int minRefuelStops(int target, int startFuel, int[][] stations) {
        PriorityQueue<Integer> heap = new PriorityQueue<>(Collections.reverseOrder());
        int i = 0;
        int result = 0;
        long fuel = startFuel;
        
        while (fuel < target) {
            while (i < stations.length && stations[i][0] <= fuel) {
                heap.offer(stations[i][1]);
                i++;
            }
            
            if (heap.isEmpty()) {
                return -1;
            }
            
            fuel += heap.poll();
            result++;
        }
        
        return result;
    }
}
