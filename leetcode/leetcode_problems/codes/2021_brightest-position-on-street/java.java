/**
 * Problem: Brightest Position on Street
 * Difficulty: Medium
 * Tags: array, sort, line sweep
 * 
 * Approach: Use line sweep - mark start and end of light coverage
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int brightestPosition(int[][] lights) {
        List<int[]> events = new ArrayList<>();
        
        for (int[] light : lights) {
            int pos = light[0];
            int range = light[1];
            events.add(new int[]{pos - range, 1});
            events.add(new int[]{pos + range + 1, -1});
        }
        
        events.sort((a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            }
            return Integer.compare(b[1], a[1]); // End before start
        });
        
        int maxBrightness = 0;
        int currentBrightness = 0;
        int resultPos = 0;
        
        for (int[] event : events) {
            int pos = event[0];
            int delta = event[1];
            currentBrightness += delta;
            if (currentBrightness > maxBrightness) {
                maxBrightness = currentBrightness;
                resultPos = pos;
            }
        }
        
        return resultPos;
    }
}