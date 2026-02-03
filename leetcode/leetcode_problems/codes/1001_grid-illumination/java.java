/**
 * Problem: Grid Illumination
 * Difficulty: Hard
 * Tags: array, hash
 * 
 * Approach: Use hash maps to track illuminated rows, columns, and diagonals
 * Time Complexity: O(lamps + queries)
 * Space Complexity: O(lamps) for hash maps
 */

import java.util.*;

class Solution {
    public int[] gridIllumination(int n, int[][] lamps, int[][] queries) {
        Map<Integer, Integer> rowCount = new HashMap<>();
        Map<Integer, Integer> colCount = new HashMap<>();
        Map<Integer, Integer> diag1Count = new HashMap<>(); // row - col
        Map<Integer, Integer> diag2Count = new HashMap<>(); // row + col
        Set<String> lampSet = new HashSet<>();
        
        for (int[] lamp : lamps) {
            int r = lamp[0], c = lamp[1];
            String key = r + "," + c;
            lampSet.add(key);
            rowCount.put(r, rowCount.getOrDefault(r, 0) + 1);
            colCount.put(c, colCount.getOrDefault(c, 0) + 1);
            diag1Count.put(r - c, diag1Count.getOrDefault(r - c, 0) + 1);
            diag2Count.put(r + c, diag2Count.getOrDefault(r + c, 0) + 1);
        }
        
        int[][] directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        List<Integer> result = new ArrayList<>();
        
        for (int[] query : queries) {
            int r = query[0], c = query[1];
            if (rowCount.getOrDefault(r, 0) > 0 || colCount.getOrDefault(c, 0) > 0 ||
                diag1Count.getOrDefault(r - c, 0) > 0 || diag2Count.getOrDefault(r + c, 0) > 0) {
                result.add(1);
            } else {
                result.add(0);
            }
            
            // Turn off lamps in 3x3 area
            for (int[] dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                String key = nr + "," + nc;
                if (lampSet.contains(key)) {
                    lampSet.remove(key);
                    rowCount.put(nr, rowCount.getOrDefault(nr, 0) - 1);
                    colCount.put(nc, colCount.getOrDefault(nc, 0) - 1);
                    diag1Count.put(nr - nc, diag1Count.getOrDefault(nr - nc, 0) - 1);
                    diag2Count.put(nr + nc, diag2Count.getOrDefault(nr + nc, 0) - 1);
                }
            }
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}