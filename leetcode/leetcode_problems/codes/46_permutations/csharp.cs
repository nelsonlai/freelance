/*
 * Problem: Permutations
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> Permute(int[] nums) {
        IList<IList<int>> result = new List<IList<int>>();
        Backtrack(result, new List<int>(), nums);
        return result;
    }
    
    private void Backtrack(IList<IList<int>> result, List<int> current, int[] nums) {
        if (current.Count == nums.Length) {
            result.Add(new List<int>(current));
            return;
        }
        
        foreach (int num in nums) {
            if (current.Contains(num)) continue;
            current.Add(num);
            Backtrack(result, current, nums);
            current.RemoveAt(current.Count - 1);
        }
    }
}