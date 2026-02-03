/**
 * Problem: Diagonal Traverse II
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Group elements by (row + col), reverse each group, concatenate
 * Time Complexity: O(n) where n is total elements
 * Space Complexity: O(n) for groups
 */

import java.util.*;

class Solution {
    public int[] findDiagonalOrder(List<List<Integer>> nums) {
        Map<Integer, List<Integer>> groups = new TreeMap<>();
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.get(i).size(); j++) {
                groups.computeIfAbsent(i + j, k -> new ArrayList<>()).add(nums.get(i).get(j));
            }
        }
        
        List<Integer> result = new ArrayList<>();
        for (List<Integer> group : groups.values()) {
            Collections.reverse(group);
            result.addAll(group);
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}