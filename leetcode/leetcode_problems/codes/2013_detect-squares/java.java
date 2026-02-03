/**
 * Problem: Detect Squares
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Store points in hash map, for query check all possible squares
 * Time Complexity: O(n) for count where n is number of points
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class DetectSquares {
    private Map<String, Integer> points;

    public DetectSquares() {
        points = new HashMap<>();
    }

    public void add(int[] point) {
        String key = point[0] + "," + point[1];
        points.put(key, points.getOrDefault(key, 0) + 1);
    }

    public int count(int[] point) {
        int x = point[0], y = point[1];
        int result = 0;
        
        for (Map.Entry<String, Integer> entry : points.entrySet()) {
            String[] parts = entry.getKey().split(",");
            int px = Integer.parseInt(parts[0]);
            int py = Integer.parseInt(parts[1]);
            
            if (px == x && py == y) {
                continue;
            }
            
            // Check if can form square: (x, y), (px, py), (x, py), (px, y)
            if (Math.abs(px - x) == Math.abs(py - y) && Math.abs(px - x) > 0) {
                String corner1 = x + "," + py;
                String corner2 = px + "," + y;
                
                if (points.containsKey(corner1) && points.containsKey(corner2)) {
                    result += entry.getValue() * points.get(corner1) * points.get(corner2);
                }
            }
        }
        
        return result;
    }
}

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares obj = new DetectSquares();
 * obj.add(point);
 * int param_2 = obj.count(point);
 */