/*
 * Problem: Permutations II
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;
using System.Linq;

public class Solution {
    public IList<IList<int>> PermuteUnique(int[] nums) {
        System.Array.Sort(nums);
        IList<IList<int>> result = new List<IList<int>>();
        bool[] used = new bool[nums.Length];
        Backtrack(result, new List<int>(), nums, used);
        return result;
    }
    
    private void Backtrack(IList<IList<int>> result, List<int> current, 
                           int[] nums, bool[] used) {
        if (current.Count == nums.Length) {
            result.Add(new List<int>(current));
            return;
        }
        
        for (int i = 0; i < nums.Length; i++) {
            if (used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1])) {
                continue;
            }
            used[i] = true;
            current.Add(nums[i]);
            Backtrack(result, current, nums, used);
            current.RemoveAt(current.Count - 1);
            used[i] = false;
        }
    }
}