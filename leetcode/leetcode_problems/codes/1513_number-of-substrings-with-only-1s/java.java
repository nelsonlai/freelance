/**
 * Problem: Number of Substrings With Only 1s
 * Difficulty: Medium
 * Tags: string, tree, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int numSub(String s) {
        int MOD = 1000000007;
        long result = 0;
        int count = 0;
        
        for (char c : s.toCharArray()) {
            if (c == '1') {
                count++;
                result = (result + count) % MOD;
            } else {
                count = 0;
            }
        }
        
        return (int) result;
    }
}