/**
 * Problem: H-Index
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int hIndex(int[] citations) {
        Arrays.sort(citations);
        
        for (int i = 0; i < citations.length; i++) {
            if (i + 1 > citations[citations.length - 1 - i]) {
                return i;
            }
        }
        
        return citations.length;
    }
}