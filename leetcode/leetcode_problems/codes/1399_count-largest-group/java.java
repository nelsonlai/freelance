/**
 * Problem: Count Largest Group
 * Difficulty: Easy
 * Tags: math, hash
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int countLargestGroup(int n) {
        Map<Integer, Integer> groups = new HashMap<>();
        for (int i = 1; i <= n; i++) {
            int sum = digitSum(i);
            groups.put(sum, groups.getOrDefault(sum, 0) + 1);
        }
        
        int maxSize = Collections.max(groups.values());
        int count = 0;
        for (int size : groups.values()) {
            if (size == maxSize) {
                count++;
            }
        }
        
        return count;
    }
    
    private int digitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
}