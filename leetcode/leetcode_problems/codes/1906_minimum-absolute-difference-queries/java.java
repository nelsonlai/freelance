/**
 * Problem: Minimum Absolute Difference Queries
 * Difficulty: Medium
 * Tags: array, hash, prefix sum
 * 
 * Approach: For each query, find all distinct numbers in range, compute min diff
 * Time Complexity: O(n * 100 + q * 100) where q is queries, numbers are 1-100
 * Space Complexity: O(n * 100)
 */

class Solution {
    public int[] minDifference(int[] nums, int[][] queries) {
        int n = nums.length;
        int[][] prefix = new int[n + 1][101];
        
        for (int i = 0; i < n; i++) {
            System.arraycopy(prefix[i], 0, prefix[i + 1], 0, 101);
            prefix[i + 1][nums[i]]++;
        }
        
        int[] result = new int[queries.length];
        for (int idx = 0; idx < queries.length; idx++) {
            int l = queries[idx][0];
            int r = queries[idx][1];
            
            List<Integer> distinct = new ArrayList<>();
            for (int i = 1; i <= 100; i++) {
                if (prefix[r + 1][i] - prefix[l][i] > 0) {
                    distinct.add(i);
                }
            }
            
            if (distinct.size() < 2) {
                result[idx] = -1;
            } else {
                int minDiff = Integer.MAX_VALUE;
                for (int i = 0; i < distinct.size() - 1; i++) {
                    minDiff = Math.min(minDiff, distinct.get(i + 1) - distinct.get(i));
                }
                result[idx] = minDiff;
            }
        }
        
        return result;
    }
}