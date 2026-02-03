/**
 * Problem: Count Unhappy Friends
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int unhappyFriends(int n, int[][] preferences, int[][] pairs) {
        Map<Integer, Map<Integer, Integer>> prefMap = new HashMap<>();
        for (int i = 0; i < n; i++) {
            Map<Integer, Integer> map = new HashMap<>();
            for (int rank = 0; rank < preferences[i].length; rank++) {
                map.put(preferences[i][rank], rank);
            }
            prefMap.put(i, map);
        }
        
        Map<Integer, Integer> pairMap = new HashMap<>();
        for (int[] pair : pairs) {
            pairMap.put(pair[0], pair[1]);
            pairMap.put(pair[1], pair[0]);
        }
        
        Set<Integer> unhappy = new HashSet<>();
        
        for (int x = 0; x < n; x++) {
            int y = pairMap.get(x);
            for (int u = 0; u < n; u++) {
                if (u != x && u != y) {
                    int v = pairMap.get(u);
                    int xPrefU = prefMap.get(x).getOrDefault(u, n);
                    int xPrefY = prefMap.get(x).getOrDefault(y, n);
                    int uPrefX = prefMap.get(u).getOrDefault(x, n);
                    int uPrefV = prefMap.get(u).getOrDefault(v, n);
                    
                    if (xPrefU < xPrefY && uPrefX < uPrefV) {
                        unhappy.add(x);
                        unhappy.add(u);
                    }
                }
            }
        }
        
        return unhappy.size();
    }
}