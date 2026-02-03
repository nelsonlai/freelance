/**
 * Problem: Random Pick with Weight
 * Difficulty: Medium
 * Tags: array, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    private int[] prefixSum;
    private int total;
    private Random random;

    public Solution(int[] w) {
        this.random = new Random();
        this.prefixSum = new int[w.length];
        int sum = 0;
        for (int i = 0; i < w.length; i++) {
            sum += w[i];
            prefixSum[i] = sum;
        }
        this.total = sum;
    }
    
    public int pickIndex() {
        int target = random.nextInt(total) + 1;
        int left = 0, right = prefixSum.length - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (prefixSum[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(w);
 * int param_1 = obj.pickIndex();
 */