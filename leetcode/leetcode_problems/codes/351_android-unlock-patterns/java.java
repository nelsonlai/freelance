/**
 * Problem: Android Unlock Patterns
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private int count = 0;
    private Map<String, Integer> skip = new HashMap<>();
    
    public int numberOfPatterns(int m, int n) {
        skip.put("1,3", 2);
        skip.put("3,1", 2);
        skip.put("1,7", 4);
        skip.put("7,1", 4);
        skip.put("3,9", 6);
        skip.put("9,3", 6);
        skip.put("7,9", 8);
        skip.put("9,7", 8);
        skip.put("1,9", 5);
        skip.put("9,1", 5);
        skip.put("2,8", 5);
        skip.put("8,2", 5);
        skip.put("3,7", 5);
        skip.put("7,3", 5);
        skip.put("4,6", 5);
        skip.put("6,4", 5);
        
        for (int i = 1; i <= 9; i++) {
            Set<Integer> visited = new HashSet<>();
            visited.add(i);
            dfs(visited, i, 1, m, n);
        }
        
        return count;
    }
    
    private void dfs(Set<Integer> visited, int last, int length, int m, int n) {
        if (length >= m) {
            count++;
        }
        if (length == n) {
            return;
        }
        
        for (int i = 1; i <= 9; i++) {
            if (visited.contains(i)) {
                continue;
            }
            
            String edge = last + "," + i;
            if (skip.containsKey(edge) && !visited.contains(skip.get(edge))) {
                continue;
            }
            
            visited.add(i);
            dfs(visited, i, length + 1, m, n);
            visited.remove(i);
        }
    }
}