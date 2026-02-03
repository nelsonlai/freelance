/**
 * Problem: K Empty Slots
 * Difficulty: Hard
 * Tags: array, tree, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int kEmptySlots(int[] bulbs, int k) {
        int n = bulbs.length;
        int[] days = new int[n];
        for (int day = 0; day < n; day++) {
            days[bulbs[day] - 1] = day + 1;
        }
        
        int left = 0, right = k + 1;
        int result = Integer.MAX_VALUE;
        
        while (right < n) {
            int maxDay = Math.max(days[left], days[right]);
            boolean valid = true;
            
            for (int i = left + 1; i < right; i++) {
                if (days[i] < maxDay) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                result = Math.min(result, maxDay);
            }
            
            left = right;
            right = left + k + 1;
        }
        
        return result == Integer.MAX_VALUE ? -1 : result;
    }
}