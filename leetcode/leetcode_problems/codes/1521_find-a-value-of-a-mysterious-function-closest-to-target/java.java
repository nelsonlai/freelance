/**
 * Problem: Find a Value of a Mysterious Function Closest to Target
 * Difficulty: Hard
 * Tags: array, tree, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int closestToTarget(int[] arr, int target) {
        int result = Integer.MAX_VALUE;
        
        for (int i = 0; i < arr.length; i++) {
            int currentAnd = arr[i];
            result = Math.min(result, Math.abs(currentAnd - target));
            
            for (int j = i + 1; j < arr.length; j++) {
                currentAnd &= arr[j];
                result = Math.min(result, Math.abs(currentAnd - target));
                
                if (currentAnd < target) {
                    break;
                }
            }
        }
        
        return result;
    }
}