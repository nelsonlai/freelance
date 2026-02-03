/**
 * Problem: Count The Repetitions
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int getMaxRepetitions(String s1, int n1, String s2, int n2) {
        if (s2 == null || s2.length() == 0) {
            return 0;
        }
        
        int s1Count = 0;
        int s2Count = 0;
        int index = 0;
        Map<Integer, int[]> recall = new HashMap<>();
        
        while (s1Count < n1) {
            for (char c : s1.toCharArray()) {
                if (c == s2.charAt(index)) {
                    index++;
                    if (index == s2.length()) {
                        s2Count++;
                        index = 0;
                    }
                }
            }
            
            s1Count++;
            
            if (recall.containsKey(index)) {
                int[] prev = recall.get(index);
                int cycleS1 = s1Count - prev[0];
                int cycleS2 = s2Count - prev[1];
                int remainingCycles = (n1 - s1Count) / cycleS1;
                s1Count += remainingCycles * cycleS1;
                s2Count += remainingCycles * cycleS2;
            } else {
                recall.put(index, new int[]{s1Count, s2Count});
            }
        }
        
        return s2Count / n2;
    }
}