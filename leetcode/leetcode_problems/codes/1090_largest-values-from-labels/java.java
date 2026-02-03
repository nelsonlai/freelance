/**
 * Problem: Largest Values From Labels
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort
 * 
 * Approach: Sort by value descending, greedily select respecting label limits
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for items and label counts
 */

import java.util.*;

class Solution {
    public int largestValsFromLabels(int[] values, int[] labels, int numWanted, int useLimit) {
        List<int[]> items = new ArrayList<>();
        for (int i = 0; i < values.length; i++) {
            items.add(new int[]{values[i], labels[i]});
        }
        items.sort((a, b) -> b[0] - a[0]);
        
        Map<Integer, Integer> labelCount = new HashMap<>();
        int result = 0;
        int count = 0;
        
        for (int[] item : items) {
            int value = item[0], label = item[1];
            if (count >= numWanted) {
                break;
            }
            if (labelCount.getOrDefault(label, 0) < useLimit) {
                result += value;
                labelCount.put(label, labelCount.getOrDefault(label, 0) + 1);
                count++;
            }
        }
        
        return result;
    }
}