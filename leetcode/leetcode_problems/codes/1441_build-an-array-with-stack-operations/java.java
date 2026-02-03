/**
 * Problem: Build an Array With Stack Operations
 * Difficulty: Medium
 * Tags: array, stack
 * 
 * Approach: Simulate - push numbers 1 to n, pop if not in target
 * Time Complexity: O(n) where n is max number
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public List<String> buildArray(int[] target, int n) {
        Set<Integer> targetSet = new HashSet<>();
        for (int t : target) {
            targetSet.add(t);
        }
        
        List<String> result = new ArrayList<>();
        int targetIdx = 0;
        
        for (int i = 1; i <= n && targetIdx < target.length; i++) {
            result.add("Push");
            if (!targetSet.contains(i)) {
                result.add("Pop");
            } else {
                targetIdx++;
            }
        }
        
        return result;
    }
}