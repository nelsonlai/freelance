/**
 * Problem: Find the Minimum Number of Fibonacci Numbers Whose Sum Is K
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: Generate Fibonacci numbers up to k, greedily subtract largest
 * Time Complexity: O(log k)
 * Space Complexity: O(log k) for Fibonacci list
 */

import java.util.*;

class Solution {
    public int findMinFibonacciNumbers(int k) {
        List<Integer> fib = new ArrayList<>();
        fib.add(1);
        fib.add(1);
        
        while (fib.get(fib.size() - 1) < k) {
            fib.add(fib.get(fib.size() - 1) + fib.get(fib.size() - 2));
        }
        
        int count = 0;
        int i = fib.size() - 1;
        while (k > 0) {
            if (fib.get(i) <= k) {
                k -= fib.get(i);
                count++;
            }
            i--;
        }
        
        return count;
    }
}