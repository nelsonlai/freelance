/**
 * Problem: Magical String
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int magicalString(int n) {
        if (n == 0) {
            return 0;
        }
        
        List<Integer> s = new ArrayList<>();
        s.add(1);
        s.add(2);
        s.add(2);
        int i = 2;
        
        while (s.size() < n) {
            int nextNum = 3 - s.get(s.size() - 1);
            int count = s.get(i);
            for (int j = 0; j < count; j++) {
                s.add(nextNum);
            }
            i++;
        }
        
        int result = 0;
        for (int j = 0; j < n; j++) {
            if (s.get(j) == 1) {
                result++;
            }
        }
        
        return result;
    }
}