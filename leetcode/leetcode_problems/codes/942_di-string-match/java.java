/**
 * Problem: DI String Match
 * Difficulty: Easy
 * Tags: array, string, greedy
 * 
 * Approach: Greedy - use smallest available number for 'I', largest for 'D'
 * Time Complexity: O(n)
 * Space Complexity: O(n) for result array
 */

class Solution {
    public int[] diStringMatch(String s) {
        int n = s.length();
        int[] result = new int[n + 1];
        int low = 0, high = n;
        
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == 'I') {
                result[i] = low++;
            } else {
                result[i] = high--;
            }
        }
        result[n] = low; // or high, they're equal now
        
        return result;
    }
}