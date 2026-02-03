/*
 * Problem: Combination Sum
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> CombinationSum(int[] candidates, int target) {
        IList<IList<int>> result = new List<IList<int>>();
        Backtrack(candidates, target, 0, new List<int>(), result);
        return result;
    }
    
    private void Backtrack(int[] candidates, int target, int start, List<int> path, IList<IList<int>> result) {
        if (target == 0) {
            result.Add(new List<int>(path));
            return;
        }
        if (target < 0) {
            return;
        }
        
        for (int i = start; i < candidates.Length; i++) {
            path.Add(candidates[i]);
            Backtrack(candidates, target - candidates[i], i, path, result);
            path.RemoveAt(path.Count - 1);
        }
    }
}