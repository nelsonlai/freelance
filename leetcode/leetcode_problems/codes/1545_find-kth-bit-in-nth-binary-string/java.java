/**
 * Problem: Find Kth Bit in Nth Binary String
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public char findKthBit(int n, int k) {
        return getBit(n, k);
    }
    
    private char getBit(int n, int k) {
        if (n == 1) {
            return '0';
        }
        
        int length = (1 << n) - 1;
        int mid = length / 2 + 1;
        
        if (k == mid) {
            return '1';
        } else if (k < mid) {
            return getBit(n - 1, k);
        } else {
            char bit = getBit(n - 1, length - k + 1);
            return bit == '0' ? '1' : '0';
        }
    }
}