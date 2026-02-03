/*
 * Problem: K-th Smallest in Lexicographical Order
 * Difficulty: Hard
 * Tags: graph
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
private:
    long long countNumbers(long long prefix, int n) {
        long long count = 0;
        long long nextPrefix = prefix + 1;
        long long current = prefix;
        
        while (current <= n) {
            count += min(nextPrefix, (long long)(n + 1)) - current;
            current *= 10;
            nextPrefix *= 10;
        }
        
        return count;
    }

public:
    int findKthNumber(int n, int k) {
        long long current = 1;
        k--;
        
        while (k > 0) {
            long long count = countNumbers(current, n);
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
};