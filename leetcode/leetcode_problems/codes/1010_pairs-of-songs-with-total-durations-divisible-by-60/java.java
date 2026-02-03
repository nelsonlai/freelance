/**
 * Problem: Pairs of Songs With Total Durations Divisible by 60
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Count remainders modulo 60, find pairs that sum to 60 or 0
 * Time Complexity: O(n)
 * Space Complexity: O(60) = O(1)
 */

import java.util.*;

class Solution {
    public int numPairsDivisibleBy60(int[] time) {
        Map<Integer, Integer> count = new HashMap<>();
        int result = 0;
        
        for (int t : time) {
            int remainder = t % 60;
            int complement = (60 - remainder) % 60;
            result += count.getOrDefault(complement, 0);
            count.put(remainder, count.getOrDefault(remainder, 0) + 1);
        }
        
        return result;
    }
}