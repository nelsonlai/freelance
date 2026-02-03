/**
 * Problem: Put Boxes Into the Warehouse II
 * Difficulty: Medium
 * Tags: array, greedy, sort, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int maxBoxesInWarehouse(int[] boxes, int[] warehouse) {
        Arrays.sort(boxes);
        int m = warehouse.length;
        int left = 0, right = m - 1;
        int count = 0;
        int boxIdx = boxes.length - 1;
        
        while (left <= right && boxIdx >= 0) {
            if (boxes[boxIdx] <= warehouse[left]) {
                count++;
                left++;
                boxIdx--;
            } else if (boxes[boxIdx] <= warehouse[right]) {
                count++;
                right--;
                boxIdx--;
            } else {
                boxIdx--;
            }
        }
        
        return count;
    }
}