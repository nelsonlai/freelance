/**
 * Problem: K-th Smallest in Lexicographical Order
 * Difficulty: Hard
 * Tags: graph
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int findKthNumber(int n, int k) {
        long current = 1;
        k--;
        
        while (k > 0) {
            long count = countNumbers(current, n);
            if (count <= k) {
                current++;
                k -= count;
            } else {
                current *= 10;
                k--;
            }
        }
        
        return (int)current;
    }
    
    private long countNumbers(long prefix, int n) {
        long count = 0;
        long nextPrefix = prefix + 1;
        long current = prefix;
        
        while (current <= n) {
            count += Math.min(nextPrefix, n + 1) - current;
            current *= 10;
            nextPrefix *= 10;
        }
        
        return count;
    }
}