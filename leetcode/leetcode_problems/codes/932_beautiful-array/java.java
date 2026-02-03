/**
 * Problem: Beautiful Array
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Divide and conquer - split into odd and even parts, recursively build beautiful arrays
 * Time Complexity: O(n log n)
 * Space Complexity: O(n log n) for recursion stack
 */

import java.util.*;

class Solution {
    private Map<Integer, List<Integer>> memo = new HashMap<>();
    
    public int[] beautifulArray(int n) {
        memo.put(1, Arrays.asList(1));
        List<Integer> result = f(n);
        return result.stream().mapToInt(i -> i).toArray();
    }
    
    private List<Integer> f(int N) {
        if (!memo.containsKey(N)) {
            List<Integer> odds = new ArrayList<>();
            List<Integer> evens = new ArrayList<>();
            
            for (int x : f((N + 1) / 2)) {
                odds.add(2 * x - 1);
            }
            for (int x : f(N / 2)) {
                evens.add(2 * x);
            }
            
            List<Integer> combined = new ArrayList<>(odds);
            combined.addAll(evens);
            memo.put(N, combined);
        }
        return memo.get(N);
    }
}