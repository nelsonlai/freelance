/**
 * Problem: Path Crossing
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean isPathCrossing(String path) {
        Set<String> visited = new HashSet<>();
        visited.add("0,0");
        int x = 0, y = 0;
        
        Map<Character, int[]> directions = new HashMap<>();
        directions.put('N', new int[]{0, 1});
        directions.put('S', new int[]{0, -1});
        directions.put('E', new int[]{1, 0});
        directions.put('W', new int[]{-1, 0});
        
        for (char direction : path.toCharArray()) {
            int[] d = directions.get(direction);
            x += d[0];
            y += d[1];
            
            String pos = x + "," + y;
            if (visited.contains(pos)) {
                return true;
            }
            visited.add(pos);
        }
        
        return false;
    }
}