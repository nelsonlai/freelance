/**
 * Problem: Number of Pairs of Strings With Concatenation Equal to Target
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Count occurrences of each string, check all pairs that form target
 * Time Complexity: O(n * m) where n is strings, m is target length
 * Space Complexity: O(n)
 */

class Solution {
    public int numOfPairs(String[] nums, String target) {
        int result = 0;
        
        for (int i = 0; i < nums.length; i++) {
            for (int j = 0; j < nums.length; j++) {
                if (i != j && (nums[i] + nums[j]).equals(target)) {
                    result++;
                }
            }
        }
        
        return result;
    }
}