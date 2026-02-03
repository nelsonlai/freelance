/**
 * Problem: Find Array Given Subset Sums
 * Difficulty: Hard
 * Tags: array, recursion, subset sum
 * 
 * Approach: Recursively recover array from subset sums
 * Time Complexity: O(n * 2^n) where n is array length
 * Space Complexity: O(2^n)
 */

import java.util.*;

class Solution {
    public int[] recoverArray(int n, int[] sums) {
        Arrays.sort(sums);
        List<Integer> result = recover(new ArrayList<>(), sums);
        return result.stream().mapToInt(i -> i).toArray();
    }
    
    private List<Integer> recover(List<Integer> current, int[] sums) {
        if (sums.length == 1) {
            return current;
        }
        
        // Find the smallest non-zero element
        int diff = sums[1] - sums[0];
        
        // Split into two groups: with and without diff
        Map<Integer, Integer> counter = new HashMap<>();
        for (int s : sums) {
            counter.put(s, counter.getOrDefault(s, 0) + 1);
        }
        
        List<Integer> withoutDiff = new ArrayList<>();
        List<Integer> withDiff = new ArrayList<>();
        
        for (int s : sums) {
            if (counter.get(s) > 0) {
                withoutDiff.add(s);
                counter.put(s, counter.get(s) - 1);
                if (counter.getOrDefault(s + diff, 0) > 0) {
                    withDiff.add(s + diff);
                    counter.put(s + diff, counter.get(s + diff) - 1);
                }
            }
        }
        
        // Try positive diff
        if (withoutDiff.contains(diff)) {
            List<Integer> newCurrent = new ArrayList<>(current);
            newCurrent.add(diff);
            int[] newSums = withoutDiff.stream().mapToInt(i -> i).toArray();
            List<Integer> result = recover(newCurrent, newSums);
            if (result != null) {
                return result;
            }
        }
        
        // Try negative diff
        if (withDiff.contains(-diff)) {
            List<Integer> newCurrent = new ArrayList<>(current);
            newCurrent.add(-diff);
            int[] newSums = withoutDiff.stream().mapToInt(i -> i).toArray();
            List<Integer> result = recover(newCurrent, newSums);
            if (result != null) {
                return result;
            }
        }
        
        return null;
    }
}
