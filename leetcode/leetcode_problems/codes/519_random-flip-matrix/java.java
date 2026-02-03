/**
 * Problem: Random Flip Matrix
 * Difficulty: Medium
 * Tags: math, hash
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    private int m, n, total;
    private Set<Integer> flipped;
    private Random random;

    public Solution(int m, int n) {
        this.m = m;
        this.n = n;
        this.total = m * n;
        this.flipped = new HashSet<>();
        this.random = new Random();
    }
    
    public int[] flip() {
        while (true) {
            int idx = random.nextInt(total);
            if (!flipped.contains(idx)) {
                flipped.add(idx);
                return new int[]{idx / n, idx % n};
            }
        }
    }
    
    public void reset() {
        flipped.clear();
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(m, n);
 * int[] param_1 = obj.flip();
 * obj.reset();
 */