/**
 * Problem: IPO
 * Difficulty: Hard
 * Tags: array, greedy, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;
        int[][] projects = new int[n][2];
        for (int i = 0; i < n; i++) {
            projects[i][0] = capital[i];
            projects[i][1] = profits[i];
        }
        Arrays.sort(projects, (a, b) -> Integer.compare(a[0], b[0]));
        
        PriorityQueue<Integer> heap = new PriorityQueue<>(Collections.reverseOrder());
        int i = 0;
        
        for (int j = 0; j < k; j++) {
            while (i < n && projects[i][0] <= w) {
                heap.offer(projects[i][1]);
                i++;
            }
            
            if (heap.isEmpty()) {
                break;
            }
            
            w += heap.poll();
        }
        
        return w;
    }
}